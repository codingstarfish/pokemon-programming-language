<h1>Pokemon-programming-language</h1>

![C](https://img.shields.io/badge/C-Standard-00599C?style=for-the-badge&logo=c&logoColor=white)
![Flex](https://img.shields.io/badge/Flex-Lexer-blue?style=for-the-badge)
![Bison](https://img.shields.io/badge/Bison-Parser-red?style=for-the-badge)
![GCC](https://img.shields.io/badge/GCC-Compiler-green?style=for-the-badge&logo=gnu-bash&logoColor=white)
![Make](https://img.shields.io/badge/Make-Build_Tool-orange?style=for-the-badge)
![Assembly](https://img.shields.io/badge/Assembly-x86--64-lightgrey?style=for-the-badge)

본 프로젝트는 직접 설계한 프로그래밍 언어를 실행 가능한 바이너리로 변환하는 컴파일러 구현 프로젝트입니다. 언어의 문법은 포켓몬 게임의 대사 형식을 차용하였으며 컴파일러 구축을 위해 위 기술들을 활용하였습니다.


## 포켓몬 프로그래밍 언어

 
"이 세계에는 신비한 생명체들이 숲과 동굴, 바다 여기저기에 살고 있지.
우리는 이 생명체들을 포켓몬이라고 부르며, 함께 연산하고 성장해 나간단다.

자, 그럼 151마리의 포켓몬들과 함께하는 코딩의 모험을 떠날 준비는 되었느냐?
이제부터 내가 이 언어의 문법을 차근차근 설명해 주마!"



### 1. 포켓몬 잡기 (변수 선언)

"트레이너의 첫걸음은 역시 포켓몬을 잡는 것이지! 원하는 포켓몬의 이름을 부르고 '잡았다!'라고 외치면 변수가 만들어진단다. 단, 관동지방의 151마리 포켓몬만 잡을 수 있다는 걸 명심하렴!"

```
피카츄를 잡았다!  // "피카츄" 변수 선언
피죤을 잡았다!    // "피죤" 변수 선언
```

### 2. 레벨 확인하기 (값 초기화)

"잡은 포켓몬의 상태를 확인해볼까?
처음에는 숫자를 정해줘서 포켓몬의 레벨(값)을 설정할 수 있단다.
정수만 대입할 수 있으니 주의하렴!
만약 레벨을 확인하지 않는다면 값은 0으로 유지된단다."

```
피카츄는 10레벨이다. ->"피카츄"에 10 저장
피죤은 100레벨이다. ->"피죤"에 100 저장
```

### 3. 포켓몬 배틀 (사칙연산)

"포켓몬을 키우는 데 있어 배틀은 피할 수 없지!
이 세계에는 4가지의 기술이 존재하고 
모든 포켓몬은 이 4가지 기술만을 사용할수 있으니 알아두렴.
각 기술은 우리가 아는 수학 기호와 똑같은 효과를 낸단다."

```
몸통박치기! -> +
화염방사! -> -
물대포! -> * 
나뭇잎! -> /
```

배틀은 <포켓몬>를 향해 <포켓몬> <기술>! 순서로 진행되고
마지막에 <포켓몬>은 쓰러졌다. 로 끝나게 된단다.
```
꼬부기를 향해 피카츄 몸통박치기! 라이츄는 쓰러졌다. -> 꼬부기 = 피카츄 + 라이츄
뮤츠를 향해 리자몽 화염방사! 파이리는 쓰러졌다. -> 뮤츠 = 리자몽 - 파이리
이상해꽃을 향해 꼬북이 물대포! 단데기는 쓰러졌다. -> 이상해꽃 = 꼬북이*단데기
버터플을 향해 이상해씨 나뭇잎! 레트라는 쓰러졌다. -> 버터플 = 이상해씨/레트라
```

물대포와 나뭇잎은 몸통박치기나 화염방사보다 더 빨라서 먼저 계산된단다! 

```
꼬부기를 향해 피카츄 몸통박치기! 꼬북이 물대포! 단데기는 쓰러졌다. -> 꼬부기 = 피카츄 + (꼬북이*단데기) 
```
### 4. 울음소리 듣기 (값 출력)

"포켓몬이 얼마나 성장했는지 궁금하지 않니?
그럴 땐 포켓몬의 울음소리를 들어보렴.
녀석의 현재 값을 힘차게 외칠 게다!"

```
뮤츠는 기분 좋은듯이 울음소리를 냈다! -> 뮤츠에 저장된 값 출력
```


"어떠냐? 생각보다 어렵지 않지? 너도 훌륭한 포켓몬 코딩 마스터가 될 수 있을 거다!
자! 그럼 너만의 전설을 코드로 작성해 보거라! 꿈과 모험, 그리고 포켓몬의 세계로! 레츠고!"


---
## ⚖️ Disclaimer
This project is a fan-made compiler and is not affiliated with Nintendo, Game Freak, or The Pokémon Company.
All Pokémon names and related media are intellectual property of their respective owners.

**To-Do LIST**
---
- 실행방법 추가하기
- 에러 메시지 수정하기
- ~~예시 코드 추가하기~~
- 자료형 추가하기
- 비교연산자 추가하기
- 조건문 추가하기
- 반복문 추가하기
- ~~도커로 실행환경 세팅~~