#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//GLOBAL Vars
int notHex = 0; //Global flag set by certain functions to assure a HEX isn't made on accident
int notOct = 1; //Same thing as above, but for OCTAL.

//FUNCTION Defs
int whatThis(char c, char c2);


//FUNCTION to figure out if float
int thisFloat (char strF[],int j){

  int tokenj =1;
  //This will scan for DECIMAL POINT to determin FLOAT
      for(j; tokenj == 1; j++){
        tokenj = whatThis(strF[j],strF[j+1]);
        if(strF[j] == '.' && (strF[j+1] >= '0' && strF[j+1] <='9')){
          return 3;
        }
      }
          return 1;
}

//FUNCTION to scan and assure that the value is OCTAL
int thisOct (char strO[], int k){
  int octFlg = 8;
  int tokenk = 1;
  //Scans through DIGITS to assure all are OCTAL values
  while( tokenk == 1){
    tokenk = whatThis(strO[k], strO[k+1]);
    if (tokenk !=1) { break;}

    if(strO[k] >= '8'){
      octFlg = 1;
      break;
    }
    k++;
  }
  return octFlg;
}


//FUNCTION to figure out what the token is and assign int value
int whatThis (char c, char c2){
  //check if 0x or 0X for HEX return 6
  if(c=='0' && notHex == 0){
    if(c2=='x' || c2=='X'){
      return 6;
    }
  }


  //check if 0(0-7) for OCTAL return 8

  if(c == '0' && notOct == 0 && (c2 >= '0' && c2 <='7')){
      return 8;
  }



  //check if DECIMAL return 1  (
  if(c>= '0' && c<= '9'){
    return 1;

    //DEBUG printf("Digit! %c  \n",c);
  }


  //check if WORD return 2
  if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
    return 2;

    //DEBUG printf("Letter! %c  \n",c);
  }

  if ( (c>= 33 && c<=47) || (c>=58 && c<=64) || (c>=93 && c<=96) || (c>=123 && c<=126) || c == 91){
      return 100;
  }

  //check for DELIMTTER return 10
  if(c == 92 || (c >= 9 && c <=13)){
    return 10;
  }



  return 0;
}
//END of whatThis function

//MAIN STARTS HERE <------------------------------------------------------------------------\
------------------
void main (int argc, char *argv[]){

  int z;


  
  if(argc != 2){
    printf("Wrong ammount of arguments. Please try again. \n");
    return;
  }
  
  //get input string
  int strLength = strlen(argv[1]);
  char str[strLength];
  strcpy(str,argv[1]);


  printf("The str is: %s \n", str);
  printf("Str Length = %d \n", strLength);
  printf("\n");

  /* DEBUG
  for(z =0; z <= strLength; z++){
    printf("%c : %d",str[z],str[z]);
  } */


  
  //VARIABLES
  int i=0;       //iterator
  int token=0;   //token flag

  for(i; i<strLength; i++){   //iterates through str[i]
    token = whatThis(str[i],str[i+1]);

    //1 is DIGIT for DECIMAL and FloatChecker
    if (token == 1){
      notHex = 1;
      notOct = 1;

      token = thisFloat(str,i);  //CHECKS for FLOATS <-IMPORTANT FUNCTION CALLS

      if(str[i] == '0' && token != 3){
      token = thisOct(str,i);  //CHECKS for OCT
      }

      if (token == 8) { notOct = 0;}

      while(token == 1){
        printf("decimal integer: %c",str[i]);
        i++;

        for(i;token==1;i++){
          token = whatThis(str[i],str[i+1]);
          if(token != 1){ break;}
          printf("%c",str[i]);
        }
      }
      notHex = 0;


      if (token != 3){
      printf("\n");
      }
    }//END of DECIMAL

    //2 is word
    if (token == 2){
      notHex = 1;

      if(str[i] == 's'){
	 if(str[i+1] == 'i'){
	    if(str[i+2] == 'z'){
	       if(str[i+3] == 'e'){
		  if(str[i+4] == 'o'){
		     if(str[i+5] == 'f'){
		       printf("sizeof: %c%c%c%c%c%c",str[i],str[i+1],str[i+2],str[i+3],str[i+4],str[i+5]);
		       i = i+5;
		       token = 0;		       
		     }
		  }
	       }
	    }
	 }
      }

      
      while(token == 2 || token == 1){
        printf("word: %c",str[i]);
        i++;

        for(i; token==2 || token == 1; i++){
          token = whatThis(str[i],str[i+1]);
          if(token != 2){
            if(token != 1){
                break;}}
          printf("%c",str[i]);
        }
      }
      notHex = 0;

      printf("\n");
    }//END of WORDS


    //3 is for FLOATS
    int  eFlg = 0;     //These are flags to denote if scientific notation has been used.
    int  dashFlg = 0;

    if(token == 3){
      notHex = 1;
      notOct = 1;
      eFlg = 1;
      dashFlg = 1;

      while (token == 3 || token ==1){
        printf("floating point: %c",str[i]);
        i++;

        for(i; token == 3 || token == 1; i++){
          token = whatThis(str[i],str[i+1]);

          if(token != 3){
            if(token != 1){
              if(str[i]== '.'){
                printf("%c",str[i]);
                i++;
                token = whatThis(str[i],str[i+1]);
              }


              if((str[i] == 'e' || str[i] == 'E') && eFlg == 1){
                if(str[i+1] == '-' || str[i+1] == '+' || (str[i+1] >= '0' && str[i+1] <= '9')){
                eFlg = 0;
                printf("%c%c",str[i],str[i+1]);
                i = i+2;
                token = whatThis(str[i],str[i+1]);
		}
              }


            }
          }

          if(token == 3 || token == 1){
          printf("%c",str[i]);
          } else {
            i--;
            break;
          }
        }

      }
      notHex = 0;
      notOct = 1;
      printf("\n");
    }//END of FLOATS


    //6 is HEX
    if (token == 6){
      notOct = 1;

      if( !(str[i+2] >= '0' && str[i+2] <= '9') && !(str[i+2] >= 'a' && str[i+2] <= 'f') && !(str[i+2] >= 'A' && str[i+3] <= 'F') ){
        printf("decimal integer: %c",str[i]);
	token = whatThis(str[i+1],str[i+2]);
      } //THIS LINE MIGHT BE FUCKIN UP HEX <--------*

      while(token == 6){
      printf("Hex: 0%c",str[i+1]);
      i = i+2;

      for(i; (str[i] >= '0' && str[i] <= '9')||(str[i] >= 'a' && str[i] <= 'f')||(str[i] >= 'A' && str[i] <= 'F'); i++){
         printf("%c",str[i]);
       }
       i--;
       token = whatThis(str[i],str[i+1]);
       if(token != 6){break;}
      }
      notOct = 0;
      printf("\n");
    }//END of HEX


    //8 is OCTAL
    if (token == 8){
      notHex = 1;

      if( str[i] == '0' && !(str[i+1] >= '0' && str[i+1] <='7') && (str[i+1] != 'x' || str[i+1] != 'X')){
	printf("decimal integer: %c", str[i]);
        token = whatThis(str[i+1],str[i+2]);
      }

      while(token == 8){
        printf("Octal: %c",str[i]);
        i++;

        for(i; str[i] >= '0' && str[i] <= '7'; i++){
          printf("%c",str[i]);
        }

        token = whatThis(str[i],str[i+1]);
        if (token !=8) {i--; break; }
      }

      notHex = 1;
      printf("\n");
    }//END of OCTAL

    //10 is DELIMETER
    if(token == 10){
      if(str[i+1] == 't' || str[i+1] == 'v' || str[i+1] == 'f' || str[i+1] == 'n' || str[i+1] == 'r'){
	i++;
      }  
    }//END of DELIMETER

    

    //100 is C operators
    if(token == 100){


      int n = str[i];

      switch(n){

      case '(':
        printf("left parenthesis: %c",str[i]);
        break;

      case ')':
        printf("right parenthesis: %c",str[i]);
        break;

      case '[':
        printf("left bracket: %c",str[i]);
        break;

      case ']':
        printf("right bracket: %c",str[i]);
        break;

      case '{':
        printf("left brace: %c",str[i]);
        break;

      case '}':
        printf("right brace: %c",str[i]);
        break;

      case ',':
        printf("comma: %c",str[i]);
        break;

      case '~':
        printf("1s complement: %c",str[i]);
        break;

      case '?':
        printf("conditional true: %c",str[i]);
        break;

      case ':':
        printf("conditional false: %c",str[i]);
        break;
	
	
      case '.':
        printf("structure member: %c",str[i]);
        break;

      case '-':
        if(str[i+1] == '>'){
	  i++;
          break;
        }
        if(str[i+1] == '-'){
          printf("decrement: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        if(str[i+1] == '='){
          printf("minus equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("minus/subtract operator: %c",str[i]);
        break;

      case '+':
        if(str[i+1] == '+'){
          printf("increment: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        if(str[i+1] == '='){
          printf("plus equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("addition: %c",str[i]);
        break;

      case '/':
        if(str[i+1] == '='){
          printf("divide equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("division: %c",str[i]);
        break;

      case '*':
        if(str[i+1] == '='){
          printf("times equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("multiply/dereference operator: %c",str[i]);
        break;

      case '=':
        if(str[i+1] == '='){
          printf("equality test: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("assignment: %c",str[i]);
        break;

      case '>':
        if(str[i+1] == '>' && str[i+2] == '='){
          printf("shift right equals: %c%c%c",str[i],str[i+1],str[i+2]);
          i = i+2;
          break;
        }
        if(str[i+1] == '>'){
          printf("shift right: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        if(str[i+1] == '='){
          printf("greater than or equal test: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("greater than test: %c",str[i]);
        break;

      case '<':
        if(str[i+1] == '<' && str[i+2] == '='){
          printf("shift left equals: %c%c%c",str[i],str[i+1],str[i+2]);
          i = i+2;
          break;
        }
        if(str[i+1] == '<'){
          printf("shift left: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        if(str[i+1] == '='){
          printf("less than or equal test: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("less than test: %c",str[i]);
        break;

      case '|':
        if(str[i+1] == '|'){
          printf("logical OR: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        if(str[i+1] == '='){
          printf("bitwise OR equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("bitwise OR: %c",str[i]);
        break;

      case '&':
        if(str[i+1] == '&'){
          printf("logical AND: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        if(str[i+1] == '='){
          printf("bitwise AND equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("AND/address operator: %c",str[i]);
        break;
	
      case '%':
        if(str[i+1] == '='){
          printf("mod equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("mod: %c",str[i]);
        break;

      case '^':
        if(str[i+1] == '='){
          printf("bitwise XOR equals: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("bitwise XOR: %c",str[i]);
        break;

      case '!':
        if(str[i+1] == '='){
          printf("inequality test: %c%c",str[i],str[i+1]);
          i++;
          break;
        }
        printf("negate: %c",str[i]);
        break;
	
      }//END Switch
      printf("\n");
    } // END of C-OPS
  }//END of FOR BLOCK with strLength
 printf("\n");
 token = whatThis(str[i],str[i+1]);
}  //END of Main
