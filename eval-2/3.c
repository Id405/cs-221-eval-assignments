#include <stdio.h>

typedef char tiny;

tiny sum(tiny a, tiny b) {	
	unsigned char sign_a = (a >> 7);
	unsigned int significand_a = (a & 0x07) | 0x08;
	unsigned char exponent_a = (a >> 3) & 0x0f;
   	printf("a, sign: %x, significand: %x, exponent: %x\n", sign_a, significand_a, exponent_a);

	unsigned char sign_b = (b >> 7);
	unsigned int significand_b = (b & 0x07) | 0x08;
    unsigned char exponent_b = (b >> 3) & 0x0f;
   	printf("b, sign: %x, significand: %x, exponent: %x\n", sign_b, significand_b, exponent_b);

	unsigned char sign_r;
	unsigned int significand_r;
	unsigned char exponent_r = exponent_a > exponent_b ? exponent_b : exponent_a;

	unsigned int exponent_difference = exponent_a > exponent_b ? exponent_a - exponent_b : exponent_b - exponent_a;

	// align exponents
	if(exponent_difference != 0) {
    	if(exponent_a > exponent_b) {
			significand_a = significand_a << exponent_difference;
    	} else {
			significand_b = significand_b << exponent_difference;
    	}
	}

	// add significands
    if(sign_a || sign_b) {
		significand_r = significand_a > significand_b ? significand_a - significand_b : significand_b - significand_a; 
		sign_r = sign_a == 0 ? significand_b > significand_a : significand_a > significand_b;
    } else {
	 	significand_r = significand_a + significand_b;
	 	sign_r = sign_a;
   	}

   	printf("sign: %x, significand: %x, exponent: %x\n", sign_r, significand_r, exponent_r);

	int fix_down = exponent_difference + (significand_a + significand_b > 0x07) - 1;
	int round = 0;

	// rounding
	if(fix_down > 0 && (significand_r >> (fix_down - 1)) & 1) {
    	int mask = ((2 << (fix_down - 2)) - 1); // mask all bits below deciding bit for rounding 
    	if( mask & significand_r ) { // essentially, are we at tie or not
			round = 1;	
    	} else {
			round = (significand_r >> fix_down) & 1;
    	}
	}

	significand_r = (significand_r >> fix_down) + round;
	exponent_r = exponent_r + fix_down;

   	printf("sign: %x, significand: %x, exponent: %x\n", sign_r, significand_r, exponent_r);
   	
    while(!(significand_r & 0x08)  && significand_r != 0) {
        significand_r = significand_r << 1;
        exponent_r--;
    }

    significand_r = significand_r & 0x07;

    return (sign_r << 7) | (((exponent_r) & 0x0f) << 3) | significand_r;
}

// these are not perfect casting functions achieving the highest accuracy possible;
// however they are good enough for testing purposes.
// note: they also do not cast to zero properly
tiny cast_to_tiny(float n) {
    int n_int = *(int*)&n; 
	char sign = (n_int >> 31);
	char significand = (n_int >> 20) & 0x07;
	char exponent = ((n_int >> 23) - 120) & 0x0f;
	return (sign << 7) | ( (exponent) << 3) | significand;
}

float cast_from_tiny(tiny n) {
	int sign = (n >> 7);
	int significand = n & 0x07;
	int exponent = (n >> 3) & 0x0f;
	int result = ((sign << 31) | ((exponent + 120) << 23) | (significand << 20));
	return *(float*)&result;
}

int main() {
	// hmm, its difficult to parse out what is just rounding errors, and what is errors in my implementation
    // printf("%f", cast_from_tiny(sum(cast_to_tiny(-11), cast_to_tiny(0.5))));
    printf("%f", cast_from_tiny(0x77));
}
