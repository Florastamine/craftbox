
// This is experimental

//////////////////////////////////////////////////////////////
#define ASCII_SHIFT 100

void Crypto_Encrypt_String(STRING *, STRING *);
void Crypto_Decrypt_String(STRING *, STRING *);

void Crypto_Encrypt_File(STRING *); // normal encryption
void Crypto_Encrypt_File(STRING *, STRING *); // output string will be sent to receiver instead of a file
void Crypto_Encrypt_File(STRING *, int); // normal encryption with Unicode support
void Crypto_Encrypt_File(STRING *, STRING *, int); // redirect output string, and input file is Unicode

void Crypto_Decrypt_File(STRING *);
void Crypto_Decrypt_File(STRING *, STRING *);
void Crypto_Decrypt_File(STRING *, int);
void Crypto_Decrypt_File(STRING *, STRING *, int);

STRING *FileContent = str_create("");
STRING *FileContentw = str_createw("");
//////////////////////////////////////////////////////////////

void Crypto_Encrypt_String(STRING *strin, STRING *receiver) {
	
	if(!strin) return;
	
	STRING *tempstr = "#5000";
	var char_counter = 0, length = str_len(strin), tempvalue = 0;
	str_cpy(receiver,"");
	
	while(char_counter < length ) {
		
		str_cpy(tempstr, strin);
		str_clip(tempstr, char_counter);
		str_trunc(tempstr, length - char_counter - 1);
		tempvalue = str_to_asc(tempstr) + ASCII_SHIFT;
		str_for_asc(tempstr, tempvalue);
		str_cat(receiver, tempstr);
		
		char_counter += 1;
		
		wait(1);
		
	}
}

void Crypto_Decrypt_String(STRING *strin, STRING *receiver) {
	
	if(!strin) return;
	
	STRING *tempstr = "#5000";
	var char_counter = 0, length = str_len(strin), tempvalue = 0;
	str_cpy(receiver, "");
	
	while(char_counter < length) {
		
		str_cpy(tempstr, strin);
		str_clip(tempstr, char_counter);
		str_trunc(tempstr, length - char_counter - 1);
		tempvalue = str_to_asc(tempstr) - ASCII_SHIFT;
		str_for_asc(tempstr, tempvalue);
		str_cat(receiver, tempstr);
		
		char_counter += 1;
		
		wait(1);
		
	}
}

//////////////////////////////////////////////////////////////


void Crypto_Encrypt_File(STRING *string, STRING *receiver, int _Unicode) {
	
	var encryptedFile = file_open_read(string);
	if( !encryptedFile ) return;
	
	if( !_Unicode ) file_str_readto(encryptedFile, FileContent, "", 10000);
	else {
	   
	   file_str_readtow(encryptedFile, FileContentw, "", 5000);
	   
	}
	
	file_close(encryptedFile);
	
	if(receiver) { // got a customer here
		
		if(!_Unicode) Crypto_Encrypt_String(FileContent, receiver);
		else Crypto_Encrypt_String(FileContentw, receiver);
		
		while(proc_status(Crypto_Encrypt_String)) wait(1);
		
		return;
		
	}
	else { // redirect to file
		
		STRING *dump = str_create("#5000");
		STRING *dumpw = str_createw("#5000");
		
		if(!_Unicode) Crypto_Encrypt_String(FileContent, dump);
		else Crypto_Encrypt_String(FileContentw, dumpw);
		
		while(proc_status(Crypto_Encrypt_String)) wait(1);
		
		encryptedFile = file_open_write(string);
		
		if(!_Unicode ) file_str_write(encryptedFile, dump);
		else file_str_write(encryptedFile, dumpw);
		
		while(proc_status(file_str_write)) wait(1);
		
		file_close(encryptedFile);
		
		return;
		
	}
	
}

// Encrypts a Unicode file
void Crypto_Encrypt_File(STRING *string, int _Unicode) {
	
	Crypto_Encrypt_File(string, NULL, _Unicode);
	
}

// Encrypts a non-Unicode file and sends to receiver
void Crypto_Encrypt_File(STRING *string, STRING *receiver) {
	
	Crypto_Encrypt_File(string, receiver, -1);
	
}

// Encrypts a non-Unicode file
void Crypto_Encrypt_File(STRING *string) {
	
	Crypto_Encrypt_File(string, NULL, -1);
	
}

void Crypto_Decrypt_File(STRING *string, STRING *receiver, int _Unicode) {
	
	var decryptedFile = file_open_read(string);
	if( !decryptedFile ) return;
	
	if( !_Unicode ) {
		
		file_str_readto(decryptedFile, FileContent, "", 10000);
		
	}

	else file_str_readtow(decryptedFile, FileContent, "", 5000);

	file_close(decryptedFile);
	
	if(receiver) {
	   
	   Crypto_Decrypt_String(FileContent, receiver);
	   while(proc_status(Crypto_Decrypt_String)) wait(1);
	   
	   return;
	   
	}
	
	else {
	   
	   STRING *dump = "#5000";
	   
	   Crypto_Decrypt_String(FileContent, dump);
	   while(proc_status(Crypto_Decrypt_String)) wait(1);
	   
	   decryptedFile = file_open_write(string);
	   file_str_write(decryptedFile, dump);
	   
	   while(proc_status(file_str_write)) wait(1);
	   
	   file_close(decryptedFile);
	   
	   return;
	   
	}
	
}

// Simply decrypts a file
void Crypto_Decrypt_File(STRING *string) {
   
   Crypto_Decrypt_File(string, NULL, -1);
   
}

// Decrypts a file, sends to receiver
void Crypto_Decrypt_File(STRING *string, STRING *receiver) {
   
   Crypto_Decrypt_File(string, receiver, -1);
   
}

// Decrypts a Unicode file
void Crypto_Decrypt_File(STRING *string, int _Unicode) {
   
   Crypto_Decrypt_File(string, NULL, _Unicode);
   
}