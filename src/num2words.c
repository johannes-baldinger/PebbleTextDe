#include "num2words.h"
//#include "string.h"

static const char*  EINER[] = {"null", "ein", "zwei", "drei", "vier", "fünf", "sechs", "sieben", "acht", "neun"};
static const char*  ZEHNER[] = {"","zehn", "zwanzig", "dreissig", "vierzig", "fünfzig", "sechzig", "siebzig", "achtzig", "neunzig"};
static const char*  ZEHN[] = {"zehn", "elf", "zwölf", "dreizehn", "vierzehn", "fünfzehn", "sechzehn", "siebzehn", "achtzehn", "neunzehn"};

static const char* STR_UHR = "Uhr";
static const char* STR_UND = "und";
static const char* STR_MINUTEN = "Minuten";


static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

static size_t append_number(char* words, int num) {
  size_t len = 0;

   if (num >=0 && num <10 ) {
    strcat(words,EINER[num]);
    return strlen(EINER[num]);
  } else if (num >=10 && num <20) { 
    strcat(words,ZEHN[num-10]);
    return strlen(ZEHN[num-10]);
  } else if (num>=20 && num<60){
    if(num%10!=0){
      strcat(words, EINER[num%10]);
      len += strlen(EINER[num%10]);
      strcat(words, STR_UND);
      len += strlen(STR_UND);
    }
    strcat(words, ZEHNER[num/10]);
    len += strlen( ZEHNER[num/10]);
  }
  return len;
}

void fuzzy_time_to_words(int hours, int minutes, char* wordsHours, char* wordsMinutes, size_t length) {
  size_t remaining = length;
  size_t remainingHours = length;
  
  memset(wordsHours, 0, length);
  memset(wordsMinutes, 0, length);
  

  remainingHours -= append_number(wordsHours, hours);
  
  remainingHours -= append_string(wordsHours, remainingHours, " ");
  remainingHours -= append_string(wordsHours, remainingHours, STR_UHR);
  remainingHours -= append_string(wordsHours, remainingHours, " ");
  if (minutes>0){
    remaining -= append_string(wordsMinutes, remaining, STR_UND);
    remaining -= append_string(wordsMinutes, remaining, " ");
    remaining -= append_number(wordsMinutes, minutes);
    remaining -= append_string(wordsMinutes, remaining, " ");
    remaining -= append_string(wordsMinutes, remaining,  STR_MINUTEN);
  }  else {
    remaining -= append_string(wordsMinutes, remaining, " ");
  }
}  
  
