matrix matMtl;
     
texture mtlSkin1;
texture mtlSkin2;

technique makewater2
{
	pass p0
	{
		Texture[0] = <mtlSkin1>;
		
		magFilter[0] = linear;
		minFilter[0] = linear;
		mipFilter[0] = linear;
		
		ColorArg1[0] = Texture; 
		ColorOp[0] = bumpenvmap;
		ColorArg2[0] = current;
		
		TextureTransformFlags[0] = Count2;
		TextureTransform[0] = <matMtl>;
		Texcoordindex[0] = 1;
		
		
		Texture[1] = <mtlSkin2>;
		
		magFilter[1] = linear;
		minFilter[1] = linear;
		mipFilter[1] = linear;
		
		AddressU[1] = Clamp;
		AddressV[1] = Clamp;
		
		ColorArg1[1] = Texture; 
		ColorOp[1] = Modulate2x;	//Modulate/AddSigned/Modulate2x/Modulate4x/Add <----------This looks all okay
		ColorArg2[1] = Current;
		
		TextureTransformFlags[1] = count3 | projected;
		texcoordindex[1] = cameraspaceposition | 1;    // For cubemap use: cameraspacereflectionvector
	}
}

technique fallback { pass p0 { } }