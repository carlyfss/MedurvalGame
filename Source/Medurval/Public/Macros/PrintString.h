#pragma once

/** Prints a string to the viewport */
#define print(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT(Text), false)

/** Prints a string to the viewport with a key so it can overlap the message with the same key*/
#define print_k(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Blue, TEXT(Text), false)

/** 
	Example: "String %f %d %s" \n
	%f - Float \n
	%d - Integer \n
	%s - String \n\n

	How to call the function \n
	printf("String %f %d %s", 1.2f, 1, "Test") \n\n
	
	It prints "String 1.2 1 Test" to the viewport
*/
#define printf(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString(TEXT(Format), ##__VA_ARGS__), false)

/** 
	Works like the printf macro but it receives a key to overlap the message with the same key
	Better used in Tick functions
*/
#define printf_key(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.0f, FColor::Blue, FString(TEXT(Format), ##__VA_ARGS__), false)
