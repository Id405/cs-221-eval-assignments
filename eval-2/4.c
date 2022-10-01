#include <stdio.h>

typedef char tiny;

tiny mult(tiny a, tiny b) {
	unsigned char sign_a = (a >> 7);
	unsigned int significand_a = (a & 0x07) | 0x08;
	unsigned char exponent_a = (a >> 3) & 0x0f;
   	printf("a, sign: %x, significand: %x, exponent: %x\n", sign_a, significand_a, exponent_a);

	unsigned char sign_b = (b >> 7);
	unsigned int significand_b = (b & 0x07) | 0x08; // currently with this method, three bits of potential adding space are wasted
    unsigned char exponent_b = (b >> 3) & 0x0f;
   	printf("b, sign: %x, significand: %x, exponent: %x\n", sign_b, significand_b, exponent_b);

   	unsigned int a_zero = !exponent_a && !(a & 0x07);
   	unsigned int b_zero = !exponent_b && !(b & 0x07);

   	if (a_zero || b_zero) {
       	return 0;
   	}

	unsigned char sign_r = sign_a ^ sign_b;
	unsigned int significand_r = (significand_a * significand_b) >> 3;
	unsigned char exponent_r = (char) (((char) exponent_a - 7) + ((char) exponent_b - 7)  + 7);

	printf("sign: %x, significand: %x, exponent: %x\n", sign_r, significand_r, exponent_r);

	int fix_down = 0;
	unsigned int significand_temp = significand_r;
	while(significand_r & 0xFFFFFFF0) {
    	significand_r = significand_r >> 1;
    	fix_down++;
	}

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
   	
    while(!(significand_r & 0x08) && significand_r) {
        printf("test");
        significand_r = significand_r << 1;
        exponent_r--;
    }

    significand_r = significand_r & 0x07;

   	printf("sign: %x, significand: %x, exponent: %x\n", sign_r, significand_r, exponent_r);

    return (sign_r << 7) | (((exponent_r) & 0x0f) << 3) | significand_r;
}

// these are not perfect casting functions achieving the highest accuracy possible;
// however they are good enough for testing purposes.
tiny cast_to_tiny(float n) { // TODO: rounding, are these functions converting with implicit 1 incorrect?
    int n_int = *(int*)&n; 
	char sign = (n_int >> 31);
	char significand = (n_int >> 20) & 0x07;
	char exponent = ((n_int >> 23) - 120) & 0x0f;
	return (sign << 7) | ( (exponent) << 3) | significand;
}

float cast_from_tiny(tiny n) {
	if (!( n << 1 )) {
    	return 0.0;
	}
    
	int sign = (n >> 7);
	int significand = n & 0x07;
	int exponent = (n >> 3) & 0x0f;
	int result = ((((sign & 0x01) << 31) | ((exponent + 120) << 23) | (significand << 20)));
	return *(float*)&result;
}

int main() {
	printf("%f", cast_from_tiny(mult(cast_to_tiny(166.0), cast_to_tiny(2.0))));
}
