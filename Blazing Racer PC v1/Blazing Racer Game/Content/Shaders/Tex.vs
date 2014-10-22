float4x4 matWVP 	: register(c0);
float4 scrollFactor	: register(c4);
struct VS_IN
{
    float4 ObjPos   : POSITION;
    float2 UV    : TEXCOORD;
};
struct VS_OUT
{
    float4 ProjPos  : POSITION;
    float2 UV    : TEXCOORD;
};

VS_OUT main( VS_IN In )
{
    VS_OUT Out;
    Out.ProjPos = mul( matWVP, In.ObjPos );
	Out.UV = In.UV;
	Out.UV.x += scrollFactor.x;
	Out.UV.y += scrollFactor.y;
    
    return Out;
};