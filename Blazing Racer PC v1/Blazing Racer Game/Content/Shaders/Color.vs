float4x4 matWVP : register(c0);
struct VS_IN 
{
    float4 ObjPos   : POSITION;
    float4 Color    : COLOR; 
}; 
 
struct VS_OUT 
{                                             
    float4 ProjPos  : POSITION;
    float4 Color    : COLOR;
};

VS_OUT main( VS_IN In )
{
    VS_OUT Out; 
    Out.ProjPos = mul( matWVP, In.ObjPos );
    Out.Color = In.Color;
    return Out;
}