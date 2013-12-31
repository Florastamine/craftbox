//////////////////////////////////////////////////////////////////
//  
//  Use alpha transparency with Envmap
//  
//
//  By: Eric Hendrickson-Lambert (Steempipe)
//
//  If it whacks you computer.... Sorry.

texture mtlSkin1;
matrix matMtl;

Technique envmap
{
		Pass p0
		{
		
		Texture[0]=<mtlSkin1>;
		
		AddressU[0]=Clamp;
		AddressV[0]=Clamp;
		
		MagFilter[0]=Linear;
		MinFilter[0]=Linear;
		MipFilter[0]=Linear;
		
		///////////////////////////////////
		// Never trust any card's defaults		
		AlphaBlendEnable=True;  
		Zenable = True;
		ZwriteEnable = True;
		//////////////////////////////////
		
		TexCoordIndex[0]=CameraSpaceReflectionVector;
		TextureTransformFlags[0]=Count3;
		TextureTransform[0]=<matMtl>;
		
		ColorArg1[0]=Texture;
		ColorOp[0]=Selectarg1;
		
		ColorOp[1]=Disable;
		AlphaOp[1]=Disable;
	}
}