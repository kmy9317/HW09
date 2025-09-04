📑 프로젝트 개요
언리얼 엔진 5.5의 C++를 사용하여 구현한 데디케이티드 서버(Dedicated Server) 기반의 멀티플레이어 턴제 숫자 야구 게임을 구현한 프로젝트
채팅을 통해 게임이 진행되며, 서버 권한(Server Authority) 모델에 입각하여 모든 핵심 로직이 서버에서 안전하게 처리됨. 언리얼 엔진의 핵심 네트워크 기능인 
RPC(Remote Procedure Call)와 변수 복제(Variable Replication)를 깊이 있게 활용하여 안정적인 멀티플레이어 환경을 구축하는 데 중점을 두었음

✨ 주요 기능
데디케이티드 서버 기반 멀티플레이: 
모든 게임 로직과 규칙이 별도의 서버 실행 파일에서 동작하여, 모든 클라이언트에게 공정하고 안정적인 게임 환경을 제공

실시간 채팅 시스템: 
플레이어는 실시간 채팅을 통해 서로 소통하고, 정답에 해당하는 세 자리 숫자를 입력하여 게임에 참여

순차 턴제 시스템: 
플레이어들은 서버에 접속한 순서대로 턴을 부여받아 게임을 진행

턴 당 시간제한 및 패널티: 
각 턴마다 10초의 시간제한이 주어지며, 시간 내에 입력하지 않으면 기회가 1회 차감되는 패널티가 적용

동적 게임 상태 관리 및 UI 연동: 
게임의 상태를 대기(Waiting), 진행(In-Progress), 종료(Round Over)로 명확히 구분하여 관리. GameState의 상태 변화에 따라 모든 클라이언트의 UI가 실시간으로 동기화되어 변화

자동 재시작 기능: 
한 라운드가 끝나면 5초 동안 승리/무승부 결과를 표시한 후, 자동으로 다음 라운드가 시작

안정적인 접속 관리: 
서버가 최대 인원일 경우 새로운 클라이언트의 접속을 거부. (PreLogin)
게임 도중 플레이어의 접속이 끊어지면 이를 감지하고 게임이 멈추지 않도록 안전하게 처리. (Logout)

🔄 핵심 로직 흐름
대기 상태 (Waiting)
서버가 시작되고, GameState는 WaitingToStart 상태가 됨
플레이어들이 접속하면 GameMode의 AllPlayerControllers 배열에 추가됨
UI에는 대기상태 관련 메시지가 표시되고 게임 관련 UI는 숨겨짐

게임 시작 (Game Start)
지정된 인원(NumPlayersToStart)이 모두 접속하면 GameMode의 StartGame() 함수가 호출됨
GameState는 InProgress 상태로 변경되고, 첫 번째 플레이어의 턴이 시작

턴 진행 (In-Progress)
ChangePlayerTurn 함수가 다음 턴의 플레이어를 지정하고, 1초마다 CountdownTurnTime을 호출하는 타이머를 시작
UI는 현재 턴인 플레이어의 이름과 남은 시간을 실시간으로 표시
플레이어가 숫자를 추리하면 PrintChatMessageString 함수가 호출되어 결과가 판정되고, 모든 플레이어에게 결과가 전송된 후 JudgeGame 함수가 호출

라운드 종료 (Round Over)
JudgeGame에서 승리 또는 무승부 조건이 충족되면 EndRoundAndRestart 함수가 호출
GameState는 RoundOver 상태로 변경되고, 결과 메시지가 GameInfo에 기록
클라이언트 UI는 이 상태 변경을 감지하여 게임 UI를 숨기고, 최종 결과 메시지를 5초 동안 표시

재시작 (Restart)
5초가 지나면 GameMode의 PrepareNewRound 함수가 호출
ResetGame으로 모든 플레이어의 시도 횟수를 초기화하고, StartGame을 다시 호출하여 새로운 라운드를 시작. 이로써 게임 루프가 다시 반복
