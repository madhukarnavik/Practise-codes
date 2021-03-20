#include<stdio.h>
#include<math.h>

/*-----------------------Sub function starts----------------------------------------------------------------*/

void verification(int append_stream[],int id[],int length_of_dlc_stream,int length_of_bit_stream)
{
	int i,j,count=0;
	int dlc_decimal = 0,data_decimal=0;
	printf("\nReceived bit stream is: ");
	for(i=0;append_stream[i]!=' ';i++)
		printf("%d",append_stream[i]);
		
/*---------------Checking ID-------------------------------------------------------------------------------*/

	for(i=i-4,j=0;append_stream[i]!=' ';i++,j++)
	{
		if(append_stream[i]!=id[j])
		{
			printf("\nID mismatch\n");
			return;
		}
		append_stream[i] = ' ';//Removal of ID elements if equal
	}
	printf("\nID match successful\n");
	
	for(i=0;append_stream[i]!=' ';i++)
		printf("%d",append_stream[i]);
		printf("\ni: %d",i);
/*-------------------------End-----------------------------------------------------------------------------*/

/*-------------------Checking DLC--------------------------------------------------------------------------*/

	for(i=i-length_of_bit_stream;append_stream[i]!=' ';i++)
		count+=1;
	printf("\nData bits are: %d\nDLC is: ",count);
	
	for(i=0;i<length_of_dlc_stream;i++)
		dlc_decimal = dlc_decimal + (append_stream[i]*pow(2,(length_of_dlc_stream-1-i)));
		printf("%d",dlc_decimal);
		
	if(dlc_decimal == ceil(((float)count/8)))
		printf("\nDLC is correct\n");
	else
	{
		printf("\nDLC is wrong");
		return;
	}
/*-----------------------End-------------------------------------------------------------------------------*/

/*-----------------------Converting to fahrenheit----------------------------------------------------------*/

	
	printf("Final data stream is: \n");
	
	for(j=0;j<dlc_decimal;j++)
	{
		
		for(i=0;i<count;i++)
		{
			append_stream[i] = append_stream[i+1];
			printf("%d",append_stream[i]);
		}
	}
	
	for(i=0;i<count;i++)
	{
		data_decimal = data_decimal + (append_stream[i]*pow(2,(count-1-i)));
	}
		printf("\n%d",data_decimal);
	
	float temperature_fahrenheit = (data_decimal*((float)9/5)) + 32;
	
	printf("\nTemperature in fahrenheit is : %f",temperature_fahrenheit);
/*-----------------------End------------------------------------------------------------------------------*/		
		
}
/*-----------------------Sub function ends----------------------------------------------------------------*/

/*-----------------------Main function starts--------------------------------------------------------------*/

int main()
{
	int temperature_celcius, bit_stream[20], length_of_bit_stream,i;
	int dlc,dlc_stream[10],length_of_dlc_stream;
	int append_stream[30],id[4]={1,0,1,1},length_of_append_stream,j;
/*--------------Accepting temperature as data-------------------------------------------------------------*/	
	printf("Enter the temperature in celcius greater than 0\n");
	scanf("%d",&temperature_celcius);
	
	printf("Entered temperature is: %d\n",temperature_celcius);
	
/*-----------------End-------------------------------------------------------------------------------------*/

/*--------------Converting data to binary---------------------------------------------------------------*/
	
	if(	temperature_celcius>0)
	{
		while(temperature_celcius>0)
		{
			bit_stream[i] = temperature_celcius%2;
			temperature_celcius = temperature_celcius/2;
			i++;
		}
	}
	
	length_of_bit_stream = i;
	
	for(i=0;i<(length_of_bit_stream/2);i++)
	{
		int temp = bit_stream[i];
		bit_stream[i]=bit_stream[length_of_bit_stream-1-i];
		bit_stream[length_of_bit_stream-1-i] = temp;
		
	}
	//printf("Binary equivalent of data is: ");
	//for(i=0;i<length_of_bit_stream;i++)
		//printf("%d",bit_stream[i]);
		
	i=0;
	
/*--------------------------End-----------------------------------------------------------------------------*/
	
		
/*------------------------Determiming DLC-------------------------------------------------------------------*/
	dlc =  ceil(((float)length_of_bit_stream/8));
	//printf("\nDLC: %d\n",dlc);
/*------------------------End--------------------------------------------------------------------------------*/

/*--------------Converting dlc to binary---------------------------------------------------------------------*/	
	if(dlc>0)
	{
		while(dlc>0)
		{
			dlc_stream[i] = dlc%2;
			dlc = dlc/2;
			i++;
		}
	}
	length_of_dlc_stream = i;
	
	for(i=0;i<(length_of_dlc_stream/2);i++)
	{
		int temp = dlc_stream[i];
		dlc_stream[i]=dlc_stream[length_of_dlc_stream-1-i];
		dlc_stream[length_of_dlc_stream-1-i] = temp;
	}
	
	//printf("Binary equivalent of DLC is: ");
	//for(i=0;i<length_of_dlc_stream;i++)
		//printf("%d",dlc_stream[i]);
		
	i=0;
/*------------------------End-------------------------------------------------------------------------------*/

/*-------------------Appending data to dlc followed by ID---------------------------------------------------*/

	for(i=0;i<length_of_dlc_stream;i++)
		append_stream[i] = dlc_stream[i];
		
		
	for(i=i;i<length_of_bit_stream+length_of_dlc_stream;i++,j++)
		append_stream[i] = bit_stream[j];

		
	for(i=i,j=0;i<length_of_bit_stream+length_of_dlc_stream+4;i++,j++)
		append_stream[i] = id[j];
		append_stream[i] = ' ';

	
	length_of_append_stream = length_of_dlc_stream+length_of_bit_stream+4;
	
	printf("\nappended data is: ");
	for (i=0;i<	length_of_append_stream;i++)
		printf("%d",append_stream[i]);
/*---------------------------------End------------------------------------------------------------------------*/	

/*---------------Sending append stream to function------------------------------------------------------------*/
			
	verification(append_stream,id,length_of_dlc_stream,length_of_bit_stream);

}
/*---------------------------------Main function End-----------------------------------------------------------*/	
