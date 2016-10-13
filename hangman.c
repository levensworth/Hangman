#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#define MAX 6
#define INDEX 4
#define MAX_LENGTH 20
#define CLEAN_BUFFER() while(getchar() != '\n')
#define ALPHABET 26
typedef char* typeWord;
typedef char typePlayer[MAX_LENGTH];
typedef typeWord typeLibrary[INDEX];
// prototypes
int checkLetter(typePlayer player,typeWord word, char letter);
int checkWord(typePlayer player,typeWord word,char alphabet[] ,char letter, int* guesses);
void guessLetter(char* letter);
char* setWord(int index, typeLibrary words);
int play( typePlayer player, typeWord word, char alphabet[]);
int makeLibrary(typeLibrary lib);
void welcome(void);
//

int checkLetter(typePlayer player,typeWord word, char letter)
{
  int found = 0;
  for(int i = 0; word[i] != 0; i++)
    if(word[i] == letter)
      {
        player[i] = letter;

        found = 1;
      }
  return found;
}

int checkWord(typePlayer player,typeWord word,char alphabet[] ,char letter, int* guesses)
{
  int match = 1;
  if(!checkLetter(player,word, letter) && alphabet[letter - 'a'] != '*')
    (*guesses)--;

  alphabet[letter - 'a'] = '*';
  for(int i = 0; word[i] != 0; i++ )
  {
    match *= (word[i] == player[i]);
  }


  return match;
}

void guessLetter(char* letter)
{
  int lttr;
  int done = 0;

  while(!done)
  {
    printf("Please, enter a letter: " );
    lttr = getchar();
    CLEAN_BUFFER();
    if (isalpha(lttr))
      done = 1;
  }

  *letter = tolower(lttr);

}

char* setWord(int index, typeLibrary words)
{
  int take = rand() % index;
  return words[take];

}


int play( typePlayer player, typeWord word, char alphabet[])
{
  welcome();
  int win = 0;
  int guesses = MAX;

  char letter;

  while(!win && guesses)
  {
    guessLetter(&letter);
    win = checkWord(player, word, alphabet, letter, &guesses);
    printf("\n\n--%s---\n\n",player );
    printf("you have %d more tries\n", guesses );
    for(int i = 0; i < ALPHABET; i++)
      {
        putchar(alphabet[i]);
        putchar(' ');
      }
    putchar('\n');

  }
  return win;
}
int makeLibrary(typeLibrary lib)
{
  int index = 0;
  lib[index++] = "hola";
  lib[index++] = "chau";
  lib[index++] = "leon";
  lib[index++] = "claudio";
  return index;
}

void welcome(void)
{
  printf("WELCOME TO THE BASSANI'S GAME:\n" );
  printf("IN THIS GAME YOU WILL HAVE %d TRIES TO GUESS THE WORD(LETTER BY LETTER)\n", MAX);
  printf("GOOD LUCK!\n");

}


int main(void)
{
  char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  typePlayer player;
  typeLibrary library;
  int index;
  int win;
  index = makeLibrary(library);
  srand(time(NULL));
  typeWord word = setWord(index, library);
  int i;
  for(i = 0;word[i] != 0 ; i++)
    player[i] = '*';
  player[i] = 0;
  win = play(player, word,alphabet);
  if(win)
    printf("CONGRATULATION! YOU WIN THE WORD WAS %s\n",word );
  return 0;

}
