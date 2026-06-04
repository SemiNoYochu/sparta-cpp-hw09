# sparta-cpp-hw09

# [Unreal Engine] 데디케이트 서버 네트워크 아키텍처 정리

언리얼 엔진의 데디케이트 서버 설정(PIE 환경) 및 NetDriver를 통한 서버-클라이언트 간의 연결, 액터 리플리케이션, RPC 동작 구조에 대한 정리 문서입니다.

---

## 1. 초기 연결 및 커넥션 관리
* **자동 객체 생성**: 언리얼 엔진에서 서버 설정을 마치면 `NetDriver`를 통해 `UNetConnect` 객체가 자동으로 생성됩니다.
* **커넥션 관리**: 생성된 객체를 통해 서버 측의 `ClientConnections`와 클라이언트 측의 `ServerConnection`을 각각 관리합니다.

## 2. 레벨 전환 및 액터 스폰 흐름
1. **접속 및 레벨 로드**: 클라이언트가 서버에 접속을 요청하면, 서버의 `NetDriver`가 `ClientConnection`을 통해 레벨 정보를 보냅니다.
2. **레벨 오픈 확인**: 클라이언트가 레벨을 열면 `ServerConnection`을 통해 `NetDriver`로 완료 패킷을 보냅니다.
3. **액터 생성 및 동기화**: 서버의 `NetDriver`가 패킷을 수신한 후, 해당 플레이어를 관리할 `PlayerController`, `PlayerState` 등의 액터들을 스폰합니다.
4. **프록시 생성**: 서버는 `ClientConnection`을 통해 프록시 생성 정보를 보내고, 클라이언트의 `NetDriver`가 이를 수신하여 화면에 프록시를 생성합니다.

## 3. 네트워크 역할 (Role) 및 프로퍼티 동기화
* **Authority (권한)**: 서버가 가지고 있는 액터의 원본 데이터 상태입니다.
* **Autonomous Proxy (자율 프록시)**: 클라이언트가 직접 소유하고 제어하는 액터의 프록시 상태입니다.
* **프로퍼티 최신화**: 수신 측의 데이터를 최신 상태로 유지하기 위해 Replication 관련 설정을 사용하여 동기화 대상을 등록합니다.

## 4. 리플리케이션(Replication) vs RPC (Remote Procedure Call)
정보의 성격과 유지 시간에 따라 관리 방식을 다르게 적용합니다.

| 구분 | 리플리케이션 (Replication) | RPC (Remote Procedure Call) |
| :--- | :--- | :--- |
| **개념** | 데이터나 상태의 지속적인 변동을 동기화 | 일시적인 이벤트나 함수를 원격으로 실행 |
| **특징** | `bReplicates = true`, `UPROPERTY`, `DOREPLIFETIME` 사용 | `Server`, `Client`, `NetMulticast` 지정 및 `Reliable`, `UnReliable` 지정 |
| **예시** | 클라이언트 서버 접속 UI 메시지 | 채팅 메시지 전송 |

### 🎮 실전 적용 예시 (숫자 야구 게임)
* **리플리케이션 활용**: `PlayerController`에 소유(Owning)되는 UI를 제어하기 위해, 컨트롤러 내부의 `NotificationText` 같은 변수를 리플리케이션 설정하여 UI 상태를 지속해서 동기화합니다.
* **RPC 활용**: 서버와 클라이언트 간의 일시적인 채팅 메시지를 주고받을 때는 `ClientRPCPrintChatMessageString` 또는 `ServerRPCPrintChatMessageString` 같은 RPC 함수를 사용하여 처리합니다.