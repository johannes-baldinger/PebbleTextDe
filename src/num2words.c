#include "num2words.h"
#include "string.h"

static char*  EINER[] = {"null", "ein", "zwei", "drei", "vier", "fünf", "sechs", "sieben", "acht", "neun"};
static char*  ZEHNER[] = {"","zehn", "zwanzig", "dreissig", "vierzig", "fünfzig", "sechzig", "siebzig", "achtzig", "neunzig"};
static char*  ZEHN[] = {"zehn", "elf", "zwölf", "dreizehn", "vierzehn", "fünfzehn", "sechzehn", "siebzehn", "achtzehn", "neunzehn"};

static const char* STR_UHR = "Uhr";
static const char* STR_UND = "und";
static const char* STR_MINUTEN = "Minuten";


static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

char* num_to_words(int num){
  char* return_val="";
  if (num >=0 && num <10 ) {
    return_val=EINER[num];
  } else if (num >=10 && num <20) { 
    return_val=ZEHN[num-10];
  } else if (num>=20 && num<60){
    return_val=ZEHNER[num/10];
    if(num%10!=0){
      strcat(return_val, EINER[num%10]);
      strcat(return_val,STR_UND);
    }
  }
  return return_val;
}

void fuzzy_time_to_words(int hours, int minutes, char* words, size_t length) {
  size_t remaining = length;
  memset(words, 0, length);
  remaining -= append_string(words, remaining, num_to_words(hours));
  remaining -= append_string(words, remaining, " ");
  remaining -= append_string(words, remaining, STR_UHR);
  remaining -= append_string(words, remaining, " ");
  if (minutes>0){
    remaining -= append_string(words, remaining, STR_UND);
    remaining -= append_string(words, remaining, " ");
    remaining -= append_string(words, remaining, num_to_words(minutes));
    remaining -= append_string(words, remaining, " ");
    remaining -= append_string(words, remaining,  STR_MINUTEN);
  }  
}  
  
