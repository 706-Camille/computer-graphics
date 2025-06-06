# 📦 OpenGL Mathematics (GLM)


[**OpenGL Mathematics (GLM)**](https://github.com/g-truc/glm)은 OpenGL Shading Language (GLSL) 기반의 **그래픽스 소프트웨어를 위한 C++ 행렬/벡터 라이브러리**이다. 거의 대부분의 OpenGL 기반 프로그램 개발에서 GLM이 활용되기 때문에, 프로그램을 개발하기 전에 아래 명령을 실행하여 **`libglm-dev` 패키지를 설치**해야 합니다.

---

## 🖥️ Ubuntu에서 설치하기  

Ubuntu 환경에서는 다음 명령어를 실행하여 `libglm-dev` 패키지를 설치할 수 있습니다:

```bash
sudo apt install libglm-dev
```

설치가 완료되면 `pkg-config`를 이용하여 GLM 라이브러리가 정상적으로 설치되었는지 확인할 수 있습니다:

```bash
pkg-config --modversion glm
```

위 명령어를 실행했을 때 **버전 정보(예: 0.9.9.8)**가 출력되면 설치가 정상적으로 완료된 것입니다. 🚀

---

✅ **이제 GLM를 활용하여 프로젝트를 빌드할 준비가 되었습니다!**

