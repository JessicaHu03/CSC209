#include<stdio.h>

int main(){
	char phone[11];
	int input = 0302;
	int result = 0;
	scanf("%s", phone);
	while (scanf("%d", &input) == 1){
		if (input == -1){
			printf("%s\n", phone);
		} else if (input >= 0 && input <= 9) {
			printf("%c\n", phone[input]);
		} else {
			printf("%s\n", "Error");
			result = 1;
		}
	}
	return result;
}
