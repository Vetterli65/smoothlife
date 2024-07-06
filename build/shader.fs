#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

uniform vec2 resolution;
uniform vec2 alphaVec;
uniform vec2 b;
uniform vec2 d;
uniform float dt;

float ra = 21;

float grid(float x, float y){
    float tx = x / resolution.x;
    float ty = y / resolution.y;
    vec4 t = texture(texture0, vec2(tx, ty));
    return max(max(t.x, t.y), t.z);
}

float sigma(float x, float a, float alpha){
    return 1.0 / (1.0 + exp(-(x - a) * 4.0 / alpha));
}

float sigma_n(float x, float a, float b){
    return sigma(x, a, alphaVec.x) * (1.0 - sigma(x, b, alphaVec.x));
}

float sigma_m(float x, float y, float m){
    return x * (1.0 - sigma(m, 0.5, alphaVec.x)) + y * sigma(m, 0.5, alphaVec.y);
}

float s(float n, float m){
    return sigma_n(n, sigma_m(b.x, d.x, m), sigma_m(b.y, d.y, m));
}

void main(){
    float cx = fragTexCoord.x * resolution.x;
    float cy = (1 - fragTexCoord.y) * resolution.y;

    float m = 0;
    float M = 0;
    float n = 0;
    float N = 0;
    float ri = ra/3.0;

    for(float dy = -ra; dy <= ra; dy += 1.0){
        for(float dx = -ra; dx <= ra; dx += 1.0){
            float x = cx + dx;
            float y = cy + dy;
            if(dx * dx + dy * dy <= ri * ri){
                m += grid(x, y);
                M += 1.0;
            } else if(dx * dx + dy * dy <= ra * ra){
                n += grid(x, y);
                N += 1.0;
            }
        }
    }
    m /= M;
    n /= N;
    float q = s(n,m);
    float diff = 2.0 * q - 1.0;
    float v = clamp(grid(cx,cy) + dt*diff, 0.0, 1.0);

    finalColor = vec4(v, v, v, 1);
}