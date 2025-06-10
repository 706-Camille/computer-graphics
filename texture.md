# 🎨 Texture Mapping & Blending 요약 (Computer Graphics)

---

## 1. Texture Mapping 기본

- **정의**: 2D 이미지를 3D 표면에 입히는 기법
- **텍스처 좌표 (s, t)**: 각 정점에 (0~1) 사이의 좌표를 할당
- **보간**: 삼각형 내부 픽셀은 (s,t)를 보간하여 계산
- **샘플링**: 보간된 (s,t)로 텍스처 이미지에서 색상 추출

---

## 2. OpenGL에서의 사용 절차

1. `glGenTextures()` 텍스처 생성  
2. `glBindTexture()` 바인딩  
3. `glTexImage2D()` 데이터 업로드  
4. `glTexParameteri()` 필터링/래핑 설정  
5. `glUniform1i()` 셰이더에 샘플러 연결  
6. 정점에 (s, t) 좌표 지정 → `glVertexAttribPointer()`

---

## 3. Texture Address Mode

- `GL_REPEAT`: 텍스처 반복
- `GL_CLAMP_TO_EDGE`: 가장자리 픽셀 유지

---

## 4. 샘플링 문제 & 필터링

- **Aliasing**: 샘플링 부족 → 왜곡, 계단현상
- **Antialiasing**: 블러링, 다중 샘플로 완화
- **텍스처 필터링**:
  - `GL_NEAREST`: 가장 가까운 텍셀
  - `GL_LINEAR`: 주변 4개 텍셀 보간

---

## 5. Mipmap

- **해상도 단계별 텍스처 저장** (이미지 피라미드)
- 축소 시 적절한 해상도 사용 → 품질 개선
- 생성:
  ```cpp
  glGenerateMipmap(GL_TEXTURE_2D);

## 6. FSAA / MSAA

- **FSAA (Full-Scene Anti-Aliasing)**, **MSAA (Multisample Anti-Aliasing)**  
  → 픽셀 안을 여러 샘플로 나누어 aliasing을 줄이는 방식

### ✅ 작동 원리

- 픽셀 내부에 다수의 샘플 포인트 배치
- 삼각형이 포함되는 샘플 수에 따라 픽셀 색상 혼합
- 경계선이 부드럽게 보임 (aliasing 완화)

| 샘플 수 | 품질         | 성능 비용 |
|---------|--------------|------------|
| 4x      | 보통         | 낮음       |
| 8x      | 좋음         | 중간       |
| 16x     | 매우 좋음    | 높음       |

---

## 7. 고급 기법

### 🔹 Normal Mapping

- RGB 이미지로 각 픽셀의 법선 방향을 저장
- 실제로는 평평한 표면이지만, 조명 반응을 달리함 → 입체감 연출

### 🔹 Multi-Texturing

- 여러 텍스처를 하나의 프래그먼트에서 조합

#### GLSL 예시:
```glsl
uniform sampler2D s_base;
uniform sampler2D s_lightmap;
varying vec2 v_texcoord;

void main() {
  vec4 base = texture2D(s_base, v_texcoord);
  vec4 light = texture2D(s_lightmap, v_texcoord);
  gl_FragColor = base * (light + 0.25);
}


glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, tex_base);
glUniform1i(glGetUniformLocation(program, "s_base"), 0);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, tex_lightmap);
glUniform1i(glGetUniformLocation(program, "s_lightmap"), 1);

8. Alpha Blending
픽셀 색상을 배경 색상과 섞는 기법

투명도(alpha) 값을 활용
