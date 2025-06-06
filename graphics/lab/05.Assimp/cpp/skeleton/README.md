# ✅ TODO List

## 📝 Scene 파일 살펴보기
* `info.txt` 파일은 이번 실습에서 사용하는 간단한 장면 파일입니다.
* 장면 파일은 **모델 정보**와 **카메라 정보**로 구성됩니다.
* 이번 실습에서는 **1개의 모델, 1개의 카메라**로만 구성된 장면 파일을 다룹니다.
* `main.cpp` 파일의 `init_scene()` 함수에서 **장면 파일을 로딩하는 코드**를 살펴보세요.

---

## 📂 PLY 파일 살펴보기
* `./models/` 디렉토리 아래에 있는 `*.ply` 파일을 확인하세요.
* PLY 파일의 **헤더 부분**에는 파일의 구성이 요약되어 있습니다.
* 이번 실습에서 사용할 `*.ply` 파일의 구조:
  - 각 정점(Vertex)은 **xyz 삼차원 위치**와 **rgba 컬러 데이터**로 구성됨
  - 모든 폴리곤은 **삼각형(Triangle) 형태**로 구성됨

---

## 🚀 Assimp를 이용해 PLY 파일 로딩하기
### 🏗 `Mesh` 구조체 구성하기
* PLY 파일을 로딩하여 CPU 메모리에 올릴 때 사용할 자료구조인 `Mesh` 구조체를 설계하세요.
* PLY 파일의 내용에 따라 `Mesh` 구조체를 아래와 같이 구성합니다.

```cpp
struct Mesh
{
  // raw data from a file
  std::vector<glm::vec3>      positions;      // per-vertex 3D positions (raw data)
  std::vector<glm::vec4>      colors;         // per-vertex rgba colors (raw data)
  std::vector<unsigned int>   tv_indices;     // size = 3 x #triangles

  // position and colors for triangle-vertices
  std::vector<glm::vec3>      tv_positions;   // per triangle-vertex 3D position (size = 3 x #triangles)
  std::vector<glm::vec4>      tv_colors;      // per triangle-vertex rgba (size = 3 x #triangles)

  GLuint  position_buffer;    // GPU 메모리에서 vertices_buffer 위치
  GLuint  color_buffer;       // GPU 메모리에서 color_buffer 위치
};
```

---

### 🔧 `load_model()` 함수 구성하기
* [Assimp 라이브러리 홈페이지](https://assimp.sourceforge.net/lib_html/index.html)를 참고하여 `load_model()` 함수 코드를 작성하세요.
* `update_mesh_data()` 함수를 작성하여 `Mesh` 구조체 내의 **triangle soup 데이터**를 계산하세요.

---

## 🎨 GPU 버퍼 데이터 설정
* `gen_gl_buffers()` 함수와 `set_gl_buffers()` 함수를 작성하여 GPU의 **position, color 버퍼 데이터를 설정**하세요.

---

## 🖼 `draw_mesh()` 함수 구성하기
* GPU에서 설정한 **position, color 버퍼 데이터**를 이용하여 메쉬를 렌더링하세요.
* **Triangle soup 데이터**를 사용하므로 `glDrawArrays()` 함수를 이용하여 렌더링 코드를 작성하세요.

---

🚀 **이제 차근차근 구현해보세요!** 🔥
