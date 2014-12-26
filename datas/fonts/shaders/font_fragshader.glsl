#version 120

uniform sampler2D texture;

// RGB to Brightness converter
float RGB2Brigthness (vec3 c) {
    vec4 K = vec4 (0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix (vec4 (c.bg, K.wz), vec4 (c.gb, K.xy), step (c.b, c.g));
    vec4 q = mix (vec4 (p.xyw, c.r), vec4 (c.r, p.yzx), step (p.x, c.r));

    return q.x;
}

vec2 RGB2HS (vec3 c) {
	vec4 K = vec4 (0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix (vec4 (c.bg, K.wz), vec4 (c.gb, K.xy), step (c.b, c.g));
	vec4 q = mix (vec4 (p.xyw, c.r), vec4 (c.r, p.yzx), step (p.x, c.r));

	float d = q.x - min (q.w, q.y);
	float e = 1.0e-10;
	
	return vec2 (abs (q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e));
}

// HSL to RGB converter
vec3 HSL2RGB (vec3 hsl) {
	vec3 color = hsl.zzz;		// default to gray

	float v = (hsl.z <= 0.5) ? (hsl.z * (1.0 + hsl.y)) : (hsl.z + hsl.y - hsl.z * hsl.y);
	
	if (v > 0) {
		float m = hsl.z + hsl.z - v;
		float sv = (v - m) / v;
		hsl.x *= 6.0;
		float vsf = v * sv * fract (hsl.x);
		float mid1 = m + vsf;
		float mid2 = v - vsf;
		
		if (hsl.x < 1.0)
			color = vec3 (v, mid1, m);
		else if (hsl.x < 2.0)
			color = vec3 (mid2, v, m);
		else if (hsl.x < 3.0)
			color = vec3 (m, v, mid1);
		else if (hsl.x < 4.0)
			color = vec3 (m, mid2, v);
		else if (hsl.x < 5.0)
			color = vec3 (mid1, m, v);
		else if (hsl.x < 6.0)
			color = vec3 (v, m, mid2);
	}
	
	return color;
}

void main (void) {
	// Get the pixel in the texture
	vec4 pixel = texture2D (texture, gl_TexCoord[0].xy);
	
	if (pixel.x < 1.f && pixel.y < 1.f && pixel.z < 1.f) {
		// Compute the brightness of the pixel
		float fBrightness = RGB2Brigthness (pixel.rgb);//max (max (pixel.r, pixel.g), pixel.b);
		// Compute the hue and saturation of the gl_Color
		vec2 hs = RGB2HS (gl_Color.xyz);

		// And convert to RGB to obtain the final pixel
		gl_FragColor = vec4 (HSL2RGB (vec3 (hs.x, hs.y, fBrightness)), pixel.w);
	} else {
		gl_FragColor = gl_Color;
	}
}