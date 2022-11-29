// library imports
#include<Keypad.h>
#include<LiquidCrystal.h>

// Setting LED and Buzzer Ports
#define led 13
#define bz 12

// Keypad ports definition
byte pinLinhas[4] = {9, 8, 7, 6};
byte pinColuns[4] = {5, 4, 3, 2};

// Keypad matrix definition
char teclas[4][4] =
{{'1', '2', '3', 'A'}, 
 {'4', '5', '6', 'B'}, 
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}};

// Keypad creation
Keypad teclado = Keypad(makeKeymap(teclas), pinLinhas, pinColuns, 4, 4);

// LCD creation
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

// Creation of variables
int cont;																		                          // Error counter
char tecla;																		                        // Typed key receiver
String senhaMestra = "123456";													              // Master password definition
String senhaAtual = "ABCD12";													                // Setting the first password
String senhaDigit = "";															                  // Password to be entered
String novaSenha = "";															                  // New to be added

void setup(){
  // LCD size setting
  lcd.begin(16, 2);
  
  // Output definition
  pinMode(led, OUTPUT);
  pinMode(bz, OUTPUT);
}

// Função de leitura do teclado
void lerTeclado(){
  senhaDigit = "";																                      // Password to be entered is reset
  while(senhaDigit.length() < 6){												                // While the variable "senhaDigit" has less than 6 characters, it makes the sequence
    tecla = teclado.getKey();													                  // Key variable receives value read from keyboard
    if(tecla != NO_KEY){														                    // Checks if any buttons have been pressed
      lcd.print("*");															                      // Shows "*" on LCD
      senhaDigit += tecla;														                  // Variable "passwordDigit" receives the key that was typed
    }
  }  
  delay(1000);
}

// Initial display setup function
void telaInicial(){
  lcd.clear();
  lcd.print("Digite a senha:");
  lcd.setCursor(5, 1);
}

// Released access function
void acessoLiberado(){
  cont = 0;																		                          // Error counter reset
  lcd.clear(); 
  lcd.print("Senha certa!");
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
}

// Access Denied Function
void acessoNegado(){
  cont++;																		                            // Error counter is incremented
  lcd.clear();
  lcd.print("Senha errada!");
  delay(2000);
  
  if(cont == 3){																                        // Check for 3 consecutive errors
    lcd.clear();  
    lcd.print("Teclado");
    lcd.setCursor(0, 1);
    lcd.print("Bloqueado!");
    digitalWrite(bz, HIGH);													                  	// Buzzer is activated
    delay(10000);																                        // Keypad locked for 10 seconds
    digitalWrite(bz, LOW);											                  			// Buzzer is deactivated
    cont = 0;																	                          // Error counter reset
  }
}

// Master password access function
void acessoMestra(){
  cont = 0;																		                          // Error counter is reset
  lcd.clear();
  lcd.print("Senha mestra");
  lcd.setCursor(0, 1);
  lcd.print("digitada!");
  delay(2000);
  lcd.clear();
  lcd.print("Nova senha:");
  lcd.setCursor(5, 1);
  lerTeclado();																	                        // Read the new password
  novaSenha = senhaDigit;
  delay(2000);
  lcd.clear();
  lcd.print("Confirme:");														                    // Confirm the new password
  lcd.setCursor(5, 1);
  lerTeclado();
  delay(2000);
  
  if((senhaDigit == novaSenha) && (senhaDigit != senhaMestra)){					// Checks if the entered and confirmed password are the same and if they are not the same as the master password
    senhaAtual = novaSenha;														                  // Assigns the new password to the "senhaAtual" variable
  	lcd.clear();
    lcd.print("Nova senha salva");
    delay(2000);
  }
  
  else if((senhaDigit == novaSenha) && (senhaDigit == senhaMestra)){		// Checks if the entered and confirmed password are the same and if they are the same as the master password
    lcd.clear();
    lcd.print("Nao pode ser");
    lcd.setCursor(0, 1);
    lcd.print("igual a mestra");												                // Do not assign the new password to the "senhaAtual" variable
  	delay(2000);
  }
  
  else{																			                            // Checks if the entered and confirmed password are different
    lcd.clear();
    lcd.print("As senhas nao");
    lcd.setCursor(0, 1);
    lcd.print("batem!");                                                // Do not assign the new password to the "senhaAtual" variable
  	delay(2000);
  }
  
}

void loop(){
  telaInicial();																                        // Calls the "telaInicial()" function
  
  lerTeclado();																	                        // Calls the "lerTeclado()" function
  
  if(senhaDigit == senhaAtual){													                // Checks that the password entered and the current password match
    acessoLiberado();															                      // Calls the "acessoLiberado() function"
  }
  
  else if(senhaDigit == senhaMestra){											              // Checks that the password entered and the master password match
    acessoMestra();																                      // Calls the "acessoMestra()" function
  }
  
  else{																			                            // Checks if the password entered does not match the current or master password
    acessoNegado();																                      // Calls the "acessoNegado()" function
  }
}
