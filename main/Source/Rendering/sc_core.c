#ifndef sc_core

#define sc_core

#include "./Source/Rendering/sc_core.h";

//Module header files
//#include "./Source/Rendering/sc_volPart.h";
#include "./Source/Rendering/sc_hdr.h";
#include "./Source/Rendering/sc_dof.h";
#include "./Source/Rendering/sc_refract.h";
#include "./Source/Rendering/sc_reflect.h";
#include "./Source/Rendering/sc_water.h";
//#include "./Source/Rendering/sc_objShaders.h";
#include "./Source/Rendering/sc_pp.h";
#include "./Source/Rendering/sc_shadows.h";

//Modules
//#include "./Source/Rendering/sc_volPart.c";
#include "./Source/Rendering/sc_hdr.c";
#include "./Source/Rendering/sc_dof.c";
#include "./Source/Rendering/sc_refract.c";
#include "./Source/Rendering/sc_reflect.c";
#include "./Source/Rendering/sc_water.c";
//#include "./Source/Rendering/sc_objShaders.c";
#include "./Source/Rendering/sc_pp.c";
#include "./Source/Rendering/sc_shadows.c";
#include "./Source/Rendering/sc_lightRay.c";

void sc_setup() {

	// because craftbox only runs on maximum resolution
	// so using screen_size is somewhat inaccurate.
	// reset shade-c
	wait(1);
	video_set(sys_metrics(0)-1,0,0,0);
	sc_scSetup = 0;
	
	wait(2);
	
	sc_scSetup = 1;
	video_set(sys_metrics(0),0,0,0);
	
	vec_set(&sky_color,vector(1,0,0));
	
	//RT Scene
	#ifdef SC_SCENERT
		sc_map_scene = bmap_createblack(sys_metrics(0),sys_metrics(1),32);
		camera.bmap = sc_map_scene;
	#endif
	
	//DoF
	#ifdef SC_DOF
		sc_setupDepth();
		sc_setupDOF();
		sc_dof();
	#endif
	//
	
	//HDR
	#ifdef SC_HDR
		if( defaultConfig.HDR )
		{
			sc_setupHDR();
			sc_hdr();
		}
	#endif
	//
	
	//	sc_refract();
	//	sc_reflect();
	
	//Volumetric Particles
	
	/*
	
	#ifdef SC_VOLPARTS
		if(sc_bVolParts == 1)
		{
			
			sc_volParts();
			sc_mtl_volPartsCombine.skin1 = sc_map_scene;
			#ifdef SC_DOF
				sc_mtl_dof.skin1 = sc_bmap_volParts;
				sc_mtl_dofDownsample.skin2 = sc_bmap_volParts;
				#ifdef SC_HDR
					if(! defaultConfig.DOF ) sc_mtl_hdr.skin1 = sc_bmap_volParts;
				#endif
				#else
				#ifdef SC_HDR
					sc_mtl_hdr.skin1 = sc_bmap_volParts;
				#endif
			#endif
		}
	#endif
	//
	
	*/	
	
	proc_mode = PROC_LATE;
	
	while(sc_scSetup){
		
		/*
		#ifdef SC_DOF
			if( defaultConfig.DOF )
			{
				vec_set(sc_view_depth.x, camera.x);
				vec_set(sc_view_depth.pan, camera.pan);
				sc_view_depth.arc = camera.arc;
			}
		#endif
		*/
		
		#ifdef SC_REFRACT
			sc_view_refract.arc = camera.arc;
			vec_set(sc_view_refract.x,camera.x);
			vec_set(sc_view_refract.pan,camera.pan);
		#endif
		
		#ifdef SC_HDR
			//SET HDR BlURSTRENGTH + HIGHPASS + EXPOSURE
			sc_mtl_hdrBlur.skill1 = floatv(sc_hdrParams[0]);
			sc_mtl_hdrHBlur.skill1 = floatv(sc_hdrParams[1]);
			sc_mtl_hdrVBlur.skill1 = floatv(sc_hdrParams[1]);
			sc_mtl_hdrHighpass.skill1 = floatv(sc_hdrParams[2]);
			sc_mtl_hdrHighpass.skill2 = floatv(sc_hdrParams[3]);
			sc_mtl_hdrHighpass.skill3 = floatv(sc_hdrParams[4]);
			sc_mtl_hdrHighpass.skill4 = floatv(sc_hdrParams[5]);
			sc_mtl_hdrGamma3.skill1 = floatv(sc_hdrParams[6]);
			sc_mtl_hdr.skill1 = floatv(sc_hdrParams[3]);
		#endif
		
		wait(1);
	}
	
	sc_reset();
}

void sc_reset()
{
	proc_kill(4);
	
	wait(2);
	sc_setup();

}

#endif