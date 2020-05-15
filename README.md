# Final_Project


#활동사항
- 2020-05-01
```
[수행일지]
   안드로이드 --> 아두이노 송신단 제거 
```
- 2020-05-02
```
[수행일지]
   - 블루투스 연결 및 페어링 버튼생성
   - 라이브러리 2개 Merge
```

- 2020-05-03
```
[수행일지]
   - 버튼확인 및 센서값들 split한후 App상에 표시
```
- 2020-05-04
```
[수행일지]
   - 버튼오류로 인한 Rollback 
   -  ahrs 센서값 6축 아두이노 --> 안드로이드 스튜디오 Data전송.
```
- 2020-05-05
```
[수행일지]
   - Ebimu 및 Flex 센서값 송신을 위한 아두이노 코드작성

[필요연구]
   - 안드로이드 스튜디오와 동기식 데이타전송 필요, 안드로이드 스튜디오상 Lifecycle 변경 필요.
```
- 2020-05-06
```
[수행일지]
   - Ebimu 및 Flex 센서값 동기식 전송 완료, 앱 실행시 자동연결 완성, LifeCycle 구상완료.

[필요연구]
   - LifeCycle 맞춰서 코딩 및 브로드캐스팅 연구필요.
```
- 2020-05-07
```
[수행일지]
   - 데이터 수신 스레드 문제해결 (split함수 오류 -> charAt 사용해 문자열 재생성)
   - 액티비티 생명주기 문제해결 (back키 누를 시 강제종료 -> onDestroy 함수를 생성해 소켓, 스레드, in/out stream을 close)

[필요연구]
   - 브로드캐스팅을 통해 블루투스 connect/disconnect 를 판단하고 해당하는 루틴 생성
   - 멀티페어링 (소켓, 스레드) 생성구상
```

- 2020-05-08
```
[수행일지]
   - 브로드캐스트 학습 완료 및 reconnectButton 구상 완료.
[필요연구]
   - 브로드캐스트 적용
```

- 2020-05-09
```
[수행일지]
   - Jarduino HC-05 Baudrate 확인 및 브로드캐스트 리시버 학습
[필요연구]
   - 탑 다운 방식으로 멀티페어링부터 재구성 필요, Data 수신 뒤 동기화 학습 필요
```

- 2020-05-10
```
[수행일지]
   - 기존 한손으로만 하는 방식 포기 -> 동기화 위해 두 손을 동시에 하는 더블포인트 Research
[필요연구]
   - 재료 구비 필요
```

- 2020-05-11
```
[수행일지]
   - 블루투스 멀티포인트 성공, 2개의 아두이노로부터 Data받아옴.
   - 추가 라이브러리 사용. (수신측 1개의 스레드로 post한 후 main에서 왼손 오른손 나뉨)
[필요연구]
   - 소켓, 스레드를 닫는 생명주기 재 설정 필요(onDestroy)
   - 브로드캐스트 리시버로 양측 아두이노 상태 확인 필요
   - 양측이 모두 연결됐을때만 Data를 받을 수 있게 해야 동기화 가능.
   - 동기화 방법 연구 필요.
```

- 2020-05-12
```
[수행일지]
   - 블루투스 모듈 및 필요한 재료들 구입완료.
   - 불필요한 UI 수정 및 삭제 Linear layout -> Constraint Layout
[필요연구]
   - 새로운 Multipoint에 대해 수신부 코드공부 필요. 
   - 자동연결 및 브로드캐스트리시버 해결요망.
```

- 2020-05-13
```
[수행일지]
   - 물품 구입 후 2번째 Ebimu 납땜 및 동작확인 -> [윈도우10 하이퍼터미널]
[필요연구]
   - 새로운 Multipoint에 대해 수신부 코드공부 필요. 
   - 자동연결 및 브로드캐스트리시버 해결요망.
```

- 2020-05-14
```
[수행일지]
   - 멀티페어링 동작완료.
   - 앱 실행시 자동연결 할 수 있게 코드수정
   - 브로드캐스트 리시버로 왼손, 오른손 블루투스 끊길 시 그에맞는 문자열출력
[필요연구]
   - 문자열을 메세지로 변경 후 Main Handler로 보내서 각 손의 State문자열을 변화시 킬 수 있게 해야함.
   - Ebimu를 받아서 UI상 출력시키는 것 필요
   - 동기화 문제 해결요망 -> 로그로 왼손 오른손 순서확인필요.
```

- 2020-05-15
```
[수행일지]
   - 오른손 아두이노에 Ebimu 센서갑 수신 후 안드로이드 스튜디오로 송신 성공.
   - 동기화 과정으 위한 스레드로부터 수신되는 데이터 순서 확인
     - 순서는 양손 한쪽씩 들어온다(각각 6개의 데이터로 했을시)
[필요연구]
   - 오른손이 왼손보다 센서값이 3개정도 많기 때문에 오른손 데이터를 3개 추가해서 동기화 순서를 다시봐야함.
   - 두번째 액티비티로 넘어가는 동작 수행해야함.
```
