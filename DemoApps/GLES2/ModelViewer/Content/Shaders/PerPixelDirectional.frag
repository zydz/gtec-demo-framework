// BEWARE: This is a example shader and it has not been optimized for speed.


#ifdef GL_FRAGMENT_PRECISION_HIGH
  precision highp float;
#else
  precision mediump float;
#endif
 
// Camera space
uniform vec3 LightDirection;

 // Material
uniform vec4 MatAmbient;

 
varying vec4 v_Color;
varying vec3 v_Normal;

void main()
{
  // Normalize the input normal
  vec3 n = normalize(v_Normal);

  // Calc the intensity as the dot product the max prevents negative intensity values
  float intensity = max(dot(n, LightDirection), 0.0);

  gl_FragColor = (v_Color * intensity) + MatAmbient;
}
