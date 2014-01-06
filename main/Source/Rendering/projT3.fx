////////////////////////////////////////////////////////
// Projected texture (FFP) by Xd1Vo
////////////////////////////////////////////////////////

float4x4 matEffect1;
float4x4 matEffect2;
float4x4 matEffect3;

texture mtlSkin1;
texture mtlSkin2;
texture mtlSkin3;
texture entSkin1;

technique proj_tex
{

	pass p0
	{
		Texture[0] = <entSkin1>;
		Texture[1] = <mtlSkin1>; // projected shadow
		Texture[2] = <mtlSkin2>; // projected shadow
		Texture[3] = <mtlSkin3>; // projected spotlight
		
		ColorArg1[0] = Texture;
		ColorArg2[0] = Diffuse;
		ColorOp[0] = Modulate2x;
		ResultArg[0] = Temp;
		
		ColorArg1[1] = Texture;//first projection shadows
		ColorOp[1] = SelectArg1;
		
		ColorArg1[2] = Texture;
		ColorArg2[2] = Current;
		ColorOp[2] = Modulate;
		
		ColorArg1[3] = Current;
		ColorArg2[3] = Texture;
		ColorOp[3] = Add;
		
		ColorArg1[4] = Current;
		ColorArg2[4] = Temp;
		ColorOp[4] = Modulate2x;
		
		texcoordindex[0] = 1;
		
		AddressU[1] = BORDER;
		AddressV[1] = BORDER;
		BorderColor[1] = 0xffffff;  
		
		texcoordindex[1] = cameraspaceposition ; 
		TextureTransformFlags[1] = count3 | projected;
		TextureTransform[1] = <matEffect1>;
		
		AddressU[2] = BORDER;
		AddressV[2] = BORDER;
		BorderColor[2] = 0xffffff;  
		
		texcoordindex[2] = cameraspaceposition ; 
		TextureTransformFlags[2] = count3 | projected;
		TextureTransform[2] = <matEffect2>;
		
		AddressU[3] = BORDER;
		AddressV[3] = BORDER;
		BorderColor[3] = 0x000001;  
		
		texcoordindex[3] = cameraspaceposition ; 
		TextureTransformFlags[3] = count3 | projected;
		TextureTransform[3] = <matEffect3>;
		
	}
	
}
