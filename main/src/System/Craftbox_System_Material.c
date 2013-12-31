
/*
--------------------------------------------------
void MaterialCopyColor(MATERIAL *dest, MATERIAL *source)

Desc:

Returns: -
--------------------------------------------------
*/
void MaterialCopyColor(MATERIAL *dest, MATERIAL *source) {
	
	WriteLog("[ ] Copying material color...");
	NewLine();

	while(!dest || !source) wait(1);

	dest.ambient_red = source.ambient_red;
	dest.ambient_green = source.ambient_green;
	dest.ambient_blue = source.ambient_blue;

	dest.specular_red = source.specular_red;
	dest.specular_blue = source.specular_blue;

	dest.diffuse_red = source.diffuse_red;
	dest.diffuse_green = source.diffuse_green;
	dest.diffuse_blue = source.diffuse_blue;

	dest.emissive_red = source.emissive_red;
	dest.emissive_green = source.emissive_green;
	dest.emissive_blue = source.emissive_blue;
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
int MaterialSelect(var id)

Desc: Selects a material from panMat. Whenever
you choose something from the material selection window,
the appropriate material will be copied to mat_temp that
will be passed later to the "select" object when it has
gone out of scope.

Returns: -1 if id is out of range.
--------------------------------------------------
*/
int MaterialSelect(var id) {

	if(event_type == EVENT_RELEASE) return -1;
	
	WriteLog("[ ] Selecting material from list...");
	NewLine();

	// Clear evidence first
	var i = 0;
	while(i < 16) {
		
		button_state(panProp_2,i,0);
		i++;
		
	}
	
	button_state(panProp_2,(int) id,1);

	if(select) {
		
		switch(id) {
			
			case 1: // Lava
			
			mat_temp = mat_lava;	
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 2: // Marble
			
			mat_temp = mat_marble;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 3: // Smaragd
			
			mat_temp = mat_smaragd;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 4: // Lavender rose
			
			mat_temp = mat_lavenderrose;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 5: // Bitter lemon
			
			mat_temp = mat_bitterlemon;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 6: // Peach orange
			
			mat_temp = mat_peachorange;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 7: // Pure white light
			
			mat_temp = mat_purewhite;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 8: // Metallic
			
			mat_temp = mat_metal;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 9: // Pure black
			
			mat_temp = mat_black;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 10: // Soft pale lilac
			
			mat_temp = mat_palelilac;
			if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
			
			break;
			
			case 11: // Custom material #1
			
			mat_type = select_custom_mat1;
			mat_temp = mat_custom[0];
			
			/*
			a quick terrible ugly hack
			normally panMat_Sub1 will only be updated
			if you click 1 "Edit Material",
			but this hack allows you to update panMat_Sub1 directly
			without pressing that button.
			
			this can be useful if you've already opened panMat_Sub1
			and select another customizable material, the panel
			will be updated immediately without having to click
			the "Edit Material" button again.
			*/
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[0]);
			
			break;
			
			case 12: // Custom material #2
			
			mat_type = select_custom_mat2;
			mat_temp = mat_custom[1];
			
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[1]);
			
			break;
			
			case 13: // Custom material #3
			
			mat_type = select_custom_mat3;
			mat_temp = mat_custom[2];
			
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[2]);
			
			break;
			
			case 14: // Custom material #4
			mat_type = select_custom_mat4;
			mat_temp = mat_custom[3];
			
			if(is(panMat_Sub1,SHOW))
			PassMaterialDataToWindow(mat_custom[3]);
			
			break;
			
			case 15: // Default
			
			mat_type = select_mat_null;
			mat_temp = NULL;
			
			break;		
			
			default:
			
			WriteLog("!! [ERROR] id fell out of range, returns -1.");  
			NewLine();
			
			return -1;
			
			break;
			
		}
		
	}
	
	WriteLog("[X] Task completed.");
	NewLine();

}


/*
--------------------------------------------------
void ReadMaterialDataFromFile(MATERIAL *m, STRING *file)

Desc: Read material properties from a file and pass it to a
previously-defined material.

Returns: -
--------------------------------------------------
*/
void ReadMaterialDataFromFile(MATERIAL *m, STRING *file) {
	
	WriteLog("[ ] Reading material data from external file (");
	WriteLog(file);
	WriteLog(")...");
	NewLine();

	while(!m) wait(1); // wait for m to be completely created

	var vpass = file_open_read(file);
	if(!vpass) {
		
		_beep();
		
		WriteLog("!! [ERROR] Failed to open ");
		WriteLog(file);
		WriteLog(" for reading material data, returns.");
		NewLine();
		
		return;
		
	}

	// Follow this form :
	/*

	ambient_red, ambient_green, ambient_blue
	specular_red, specular_green, specular_blue,
	diffuse_red, diffuse_green, diffuse_blue,
	emissive_red, emissive_green, emissive_blue,
	alpha, power (no need for albedo)

	*/

	m.ambient_red = file_var_read(vpass);
	m.ambient_green = file_var_read(vpass);
	m.ambient_blue = file_var_read(vpass);

	m.specular_red = file_var_read(vpass);
	m.specular_green = file_var_read(vpass);
	m.specular_blue = file_var_read(vpass);

	m.diffuse_red = file_var_read(vpass);
	m.diffuse_green = file_var_read(vpass);
	m.diffuse_blue = file_var_read(vpass);

	m.emissive_red = file_var_read(vpass);
	m.emissive_green = file_var_read(vpass);
	m.emissive_blue = file_var_read(vpass);

	m.alpha = file_var_read(vpass);
	m.power = file_var_read(vpass);

	file_close(vpass);
	
	WriteLog("[X] Task completed.");
	NewLine();
}

/*
--------------------------------------------------
void PassMaterialDataToWindow(MATERIAL *m)

Desc: Copies material data from m to the material
properties window.

Returns: - 
--------------------------------------------------
*/
void PassMaterialDataToWindow(MATERIAL *m) {
	
	WriteLog("[ ] Passing material data to the appropriate panel...");
	NewLine();

	while(!m) wait(1);
	if(!is(panMat_Sub1,SHOW)) return;

	v_ambient_r = m.ambient_red;
	v_ambient_g = m.ambient_green;
	v_ambient_b = m.ambient_blue;

	v_diffuse_r = m.diffuse_red;
	v_diffuse_g = m.diffuse_green;
	v_diffuse_b = m.diffuse_blue;

	v_specular_r = m.specular_red;
	v_specular_g = m.specular_green;
	v_specular_b = m.specular_blue;

	v_emissive_r = m.emissive_red;
	v_emissive_g = m.emissive_green;
	v_emissive_b = m.emissive_blue;

	v_power = m.power;
	v_alpha_m = 100 - m.alpha;
	
	WriteLog("[X] Task completed.");
	NewLine();

}

/*
--------------------------------------------------
void WriteMaterialDataToFile(STRING *file, MATERIAL *m)

Desc: Writes material data from m to file, mostly
custom materials. Or you can use this to save a predefined
material to a file and then pass it back to one of the
custom materials.

Returns: -
--------------------------------------------------
*/
void WriteMaterialDataToFile(STRING *file, MATERIAL *m) {
	
	WriteLog("[ ] Writing material data to ");
	WriteLog(file);
	NewLine();
	
	while(!m) wait(1);

	var vpass = file_open_write(file);
	if(!vpass) {
		
		_beep();
		
		WriteLog(" !! [ERROR] Failed to open ");
		WriteLog(file);
		WriteLog("for writing material data to, returns.");
		NewLine();
		
		return;
		
	}

	// Copy values from the sliders
	m.ambient_red = v_ambient_r;
	m.ambient_green = v_ambient_g;
	m.ambient_blue = v_ambient_b;

	m.specular_red = v_specular_r;
	m.specular_green = v_specular_g;
	m.specular_blue = v_specular_b;

	m.diffuse_red = v_diffuse_r;
	m.diffuse_green = v_diffuse_g;
	m.diffuse_blue = v_diffuse_b;

	m.emissive_red = v_emissive_r;
	m.emissive_green = v_emissive_g;
	m.emissive_blue = v_emissive_b;

	m.alpha = 100 - v_alpha_m;
	m.power = v_power;

	// Write these copied values to vpass handle
	file_var_write(vpass,m.ambient_red);
	file_var_write(vpass,m.ambient_green);
	file_var_write(vpass,m.ambient_blue);

	file_var_write(vpass,m.specular_red);
	file_var_write(vpass,m.specular_green);
	file_var_write(vpass,m.specular_blue);

	file_var_write(vpass,m.diffuse_red);
	file_var_write(vpass,m.diffuse_green);
	file_var_write(vpass,m.diffuse_blue);

	file_var_write(vpass,m.emissive_red);
	file_var_write(vpass,m.emissive_green);
	file_var_write(vpass,m.emissive_blue);

	file_var_write(vpass,m.alpha);
	file_var_write(vpass,m.power);

	file_close(vpass);

	// close the panel.
	if(is(panMat_Sub1,SHOW)) reset(panMat_Sub1,SHOW);
	
	WriteLog("[X] Task completed.");
	NewLine();
}

/*
--------------------------------------------------
void MaterialSave()

Desc: Saves custom materials' data to file using
WriteMaterialDataToFile. It's a WriteMaterialDataToFile
wrapper which will be assigned to the GUI buttons.

Returns: -
--------------------------------------------------
*/
void MaterialSave() {

	if(event_type == EVENT_RELEASE) return;
	
	WriteLog("Saving material to file...");
	NewLine();

	// Material saving is available only to custom materials
	switch(mat_type) {
		
		case select_custom_mat1 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_1,mat_custom[0]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat2 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_2,mat_custom[1]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat3 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_3,mat_custom[2]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		case select_custom_mat4 :
		WriteMaterialDataToFile(FILE_CUSTOM_MAT_4,mat_custom[3]);
		
		break;
		//////////////////////////////////////////////////////////////
		
		default:
		// This line will never be executed.
		//		printf("Material saving is available only to custom materials.");
		break;
	}
	
}