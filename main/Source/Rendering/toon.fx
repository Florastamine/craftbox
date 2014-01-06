texture entSkin1;				// The models skin texture
texture mtlSkin1;				// The normalisation map
texture mtlSkin2;				// The tone map   
matrix matWorldViewProj;
matrix matWorld;
vector vecSunDir;				// Sun direction vector 
	
technique TwoToneToon
{
	// -------------- Painter --------------------
	pass p0
	{
		texture[0]=<mtlSkin1>;		// The normalisation map
		texture[1]=<mtlSkin2>;		// The shade map
		texture[2]=<entSkin1>;		// The models skin texture
		
		addressU[1]=clamp;
		addressU[2]=wrap;
		addressV[2]=wrap;
		magFilter[2]=linear;
		minFilter[2]=linear;
		mipFilter[2]=linear;
		
		vertexShaderConstant[0]=<matWorldViewProj>;
		vertexShaderConstant[4]=<matWorld>;
		vertexShaderConstant[16]=<vecSunDir>;
		                        
		vertexShader=asm
		{
			vs.1.1
			dcl_position v0
			dcl_normal v3
			dcl_texcoord0 v7
			
			m4x4 oPos,v0,c0         // transform position to clip space
			m3x3 r0,v3,c4           // transform normal to world space
			dp3 r0.w,r0,r0          // renormalize it
			rsq r0.w,r0.w
			mul r0,r0,r0.w
			mov oT0.xyz,r0.xyz      // output normal to oT0
			mov oT1.xyz,-c16.xyz    // output light direction to oT1
			mov oT2.xy,v7.xy        // output uvs to ot2
		};
		pixelShader=asm
		{
			ps.1.2
			tex t0                  // fetch normalized normal
			texdp3tex t1,t0_bx2
			tex t2                  // sample color map
			mul r0,t2,t1            // modulate with shading	
		};    
	}
	// -------------- Outliner -------------------	
	pass p1
	{
		CULLMODE=CW;
		vertexShaderConstant[0]=<matWorldViewProj>;
		vertexShaderConstant[16]=0.2; // outline_thickness, def0.001 << CHANGE THIS TO CHANGE OUTLINE THICKNESS
		
		vertexShader=asm
		{
			vs.1.1
			dcl_position v0
			dcl_normal v3
			dcl_texcoord v7
			
			mov r0,v0
			mul r1,c16.x,v3            // Scale the normal
			add r0.xyz,r0.xyz,r1.xyz   // Shell offset (vertex pos + Scaled Normal)
			m4x4 oPos,r0,c0            // Transorm position to clip space
		};
		pixelShader=asm
		{
			ps.1.1
			def c0,0,0,0,1             // outline rgba << CHANGE THIS TO CHANGE OUTLINE COLOUR
			mov r0,c0
		};
	}
}	// End of technique

technique fallback  // empty fallback causes normal rendering without outline
{
	pass p0 { }
}