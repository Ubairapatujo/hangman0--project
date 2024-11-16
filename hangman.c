#include <stdio.h>
#include <stdlib.h> // for rand() and srand() functions
#include <time.h> // for srand(time(NULL)) function
#include <string.h>
#include <ctype.h>

void GuesstheWord(char *word, char *guessed_letters);
void PlayGame(char *word);
void drawHangman(int attempts);

int main(void) {
    int  random_index, category_choice;
    char choose;
    
    //  intializing and declaring 5 categories (pointers)
    char *fruits[] = {
        "apple", "orange", "banana", "grape", "kiwi", 
        "mango", "peach", "pear", "pineapple", "plum", 
        "strawberry", "blueberry", "raspberry", "watermelon", 
        "papaya", "apricot", "blackberry", "cantaloupe", 
        "dragonfruit", "pomegranate", "tangerine", "lime", 
        "lemon", "coconut", "fig", "passionfruit"
    };

    char *animals[] = {
        "lion", "tiger", "elephant", "giraffe", "zebra", 
        "kangaroo", "panda", "penguin", "dolphin", "shark", 
        "wolf", "fox", "bear", "rabbit", "deer", 
        "squirrel", "eagle", "hawk", "flamingo", "ostrich", 
        "crocodile", "hippopotamus", "rhinoceros", "koala", 
        "parrot", "tortoise", "seal"
    };

    char *countries[] = {
        "brazil", "canada", "france", "germany", "italy", 
        "spain", "japan", "india", "china", "mexico", 
        "russia", "australia", "argentina", "southafrica", 
        "netherlands", "sweden", "norway", "finland", "ireland", 
        "portugal", "switzerland", "newzealand", "belgium", 
        "austria", "denmark", "singapore", "turkey"
    };

    char *colors[] = {
        "red", "blue", "green", "yellow", "purple", 
        "orange", "pink", "black", "white", "gray", 
        "brown", "cyan", "magenta", "teal", "navy", 
        "gold", "silver", "violet", "indigo", "beige", 
        "maroon", "lavender", "turquoise", "peach", "coral"
    };

    char *sports[] = {
        "soccer", "basketball", "baseball", "tennis", "golf", 
        "cricket", "rugby", "hockey", "volleyball", "swimming", 
        "boxing", "cycling", "running", "gymnastics", "wrestling", 
        "tabletennis", "badminton", "skating", "surfing", "skiing", 
        "hiking", "fencing", "sailing", "snowboarding", "karate"
    };

    char **categories[] = {fruits, animals, countries, colors, sports};

    printf("Welcome to Hangman!\n\n");
    
    do {
    //  asking user to choose a category
    printf("Choose a category:\n");
    printf("1: Fruits\n2: Animals\n3: Countries\n4: Colors\n5: Sports");
    
    printf("\nEnter your choice (1-5): ");
    scanf("%d", &category_choice);
    
    //	checking if the user has put correct input
    if (category_choice < 1 || category_choice > 5) {
        printf("Invalid choice. Exiting the game.\n");
        return 1;
    }

    //  Get the selected category
    char **words = categories[category_choice - 1];

    //  random number generator ,it can be any large or small value till 32767
    srand(time(NULL));  
    
    //	generates a number (index) that is guaranteed to be present in our words array
    random_index = rand() % 25;

    // Start the game
    PlayGame(words[random_index]);
    printf("\nDo you want to play again? (y/n) ");
    scanf(" %c",&choose);
    printf("\n");
   } while (choose=='Y' || choose=='y');
    return 0;
}

void PlayGame(char *word) {
    char guessed_letters[26] = {0};  // To store guessed letters
    int attempts = 6; // number of attempts allowed
    char guess;
    char incorrect_guess[26] = {0};
    int k=0; 
    
    while (attempts > 0) {
        printf("\nWord to guess: ");
        GuesstheWord(word, guessed_letters); // another function
        
        drawHangman(6 - attempts); //hangman drawing
        
        printf("Wrong guesses left: %d",attempts);
        printf("\nIncorrect guesses: %s",incorrect_guess);
        printf("\nGuess a letter: ");
        scanf(" %c", &guess);
        
        guess = tolower(guess); //convert capital letter input to lowercase

        // Check if the user entered a valid alphabetic character
        if (!isalpha(guess)) {
            printf("Please enter a valid alphabetic character.\n");
            continue;
        }
        
        // check if the guessed character is already present or not (strchr is used to check first occurence of a specific character in a string)
        // str = string to be searched, chr = character to be searched
        if (strchr(guessed_letters, guess)) {
            printf("You've already guessed that letter.\n");
            continue;
        }
        
        // add the guess to guessed letters 
        // 1 is written bcz we want the guess character to be added in guessed_letters string only once
        strncat(guessed_letters, &guess, 1);
        
        // check if the guess is correct
        // check if that character is present in our words string or not
        if (!strchr(word, guess)) {
        	incorrect_guess[k] = guess;
        	k++;
            attempts--;
            printf("Incorrect!\n");
        } else {
        	printf("Good guess!\n");
		}
		
        int length = strlen(word); // length of our word
        int guessed_all = 1; // flag variable
        // iterating over our word string and checking if all the guesses user guessed is present in our word string
        for (int i = 0; i < length; i++) {
        	// if even one guess is not present then it will make our flag variable (guessed_all) 0 
        	if(!strchr(guessed_letters,word[i])) {
        		guessed_all = 0;
        		break;
			}
		}
		
		// if flag variable is 1 which means user has guessed all the values
		if (guessed_all) {
			printf("\n");
			printf("Word to guess: "); GuesstheWord(word, guessed_letters);
			printf("Congratulations! You've guessed the word: %s\n", word);
			return;
		}
    }
    if (attempts == 0) {
    	drawHangman(6 - attempts);
	}
    printf("Better luck next time\nThe word was: %s\n", word);
}
void GuesstheWord(char *word, char *guessed_letters) {
    int length = strlen(word); // length of our word
    for (int i = 0; i < length; i++) {
    	// str = string to be searched, chr = character to be searched
    	// it will iterate through every character of our word which user has to guess, and
    	// if that character is present in guess_letters string then it will be displayed
        if (strchr(guessed_letters, word[i])) {
            printf("%c ", word[i]); // Show the correct letter
        } else {
            printf("_ "); // Show placeholder for unguessed letters
        }
    }
    printf("\n");
}
void drawHangman(int attempts) {
    switch (attempts) {
        case 0:
            printf(" ___\n");
            printf("|   |\n");
            printf("|\n");
            printf("|\n");
            printf("|\n");
            printf("|\n");
            printf("|___\n");
            break;
        case 1:
            printf(" ___\n");
            printf("|   |\n");
            printf("|   O\n");
            printf("|\n");
            printf("|\n");
            printf("|\n");
            printf("|___\n");
            break;
        case 2:
            printf(" ___\n");
            printf("|   |\n");
            printf("|   O\n");
            printf("|   |\n");
            printf("|\n");
            printf("|\n");
            printf("|___\n");
            break;
        case 3:
            printf(" ___\n");
            printf("|   |\n");
            printf("|   O\n");
            printf("|   |\\\n");
            printf("|\n");
            printf("|\n");
            printf("|___\n");
            break;
        case 4:
            printf(" ___\n");
            printf("|   |\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|\n");
            printf("|\n");
            printf("|___\n");
            break;
        case 5:
            printf(" ___\n");
            printf("|   |\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|    \\\n");
            printf("|\n");
            printf("|___\n");
            break;
        case 6:
            printf(" ___\n");
            printf("|    |\n");
            printf("|    O\n");
            printf("|   /|\\\n");
            printf("|   / \\\n");
            printf("|\n");
            printf("|___\n");
            printf("Game Over! The man is hanged.\n");
            break;
    }
}