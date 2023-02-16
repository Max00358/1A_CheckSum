#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum(unsigned int n);
void add_checksum(unsigned int array[], std::size_t capacity);
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned int array[], std::size_t capacity);


#ifndef MARMOSET_TESTING
int main() {
	system("clear");
	unsigned int value_to_protect = 47763561;
	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "\nThe value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;
	
	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	} 
	std::size_t qty_values = 3;
	unsigned int value_series[3] = {20201122, 20209913, 20224012};
	
	add_checksum(value_series, qty_values);
	
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index = 0;
		series_index < qty_values; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}
	//Test remove checksum--------test value: 339120537
	std::cout << "\nRemove checksum output: " << remove_checksum(173768466);

	std::size_t qty_values_two = 3;
	unsigned int value_series_two[3] = {649660701, 593039308, 626730121};

	//Test void remove checksum
	remove_checksum(value_series_two, qty_values_two);

	std::cout << "\nVoid checksum test: ";
	for (std::size_t series_index = 0; series_index < qty_values_two; series_index++)
	{
		std::cout << value_series_two[series_index] << " ";
	}


    std::cout << std::endl;
    return 0;
}
#endif

unsigned int add_checksum(unsigned int n){
	int array_n[9];
	unsigned int tot = 0;
	int temp = n;

	if(n >= 0 && n <= 99999999){
		//Calculate checksum

		for(int i = 7; i >= 0; --i){
			array_n[i] = n%10;
			n = n / 10;
		}

		for(int j = 7; j >= 0; j = j-2){
			//check if it's "every-other num"
			if(j%2 == 1){
				
				array_n[j] = array_n[j] * 2;

				//if multiplication > 9, then add the two digits together
				if(array_n[j] > 9){
					int temp[2];

					temp[1] = array_n[j]/10;
					temp[0] = array_n[j]%10;
					array_n[j] = temp[0] + temp[1];
				}
			}
		}

		for(int m = 0; m <= 7; ++m){
			tot = tot + array_n[m];
		}

		tot = (tot * 9) % 10;
		array_n[8] = tot;

		//Testing: print out array
		//for (int i = 0; i <= 8; ++i){
		//	std::cout << "\t" << array_n[i];
		//}

		n = temp * 10 + tot;
		
		return n;
	}
	else{
		n = 4294967295;
		return n;
	}
}

void add_checksum(unsigned int array[], std::size_t capacity){
	for(int i = 0; i < capacity; ++i){
		if(array[i] >= 0 && array[i] <= 99999999){
			int array_value = array[i];
			array[i] = add_checksum(array_value);
		}
		else{
			array[i] = 4294967295;
		}
	}
	return;
}

bool verify_checksum(unsigned int n){
	int temp = n%10;
	n = n/10;
	int checksum_value = add_checksum(n)%10;

	if(n >= 0 && n <= 99999999){
		if(temp == checksum_value){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

unsigned int remove_checksum(unsigned int n){
	//int temp_n = n;
	int temp = n%10;
	n = n/10;
	int checksum_value = add_checksum(n)%10;

	if(n >= 0 && n <= 99999999){
		if(temp == checksum_value){
			return n;
		}
		else{
			return 4294967295;
		}
	}
	else{
		return 4294967295;
	}
	return 0;
}

void remove_checksum(unsigned int array[], std::size_t capacity){

	for(int i = 0; i < capacity; ++i){
		int temp = array[i] % 10;
		int checksum_value = add_checksum( array[i]/10 ) % 10;

		if( (array[i]/10 >= 0) && ( (array[i]/10) <= 99999999) ){
			if(temp == checksum_value){
				array[i] = array[i]/10;
			}
			else{
				array[i] = 4294967295;
			}
		}
		else{
			array[i] = 4294967295;
		}
	}
	return;
}