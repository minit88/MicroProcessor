# MicroProsessor

기말 텀프로젝트

프로젝트명 : ATMEGA 128 을 이용한 도어락

기능 설명 : 1.초기 비밀번호 4자리를 설정한 후 비밀번호 입력이 가능해짐 ( FND 7segment에 입력되는 숫자 표시)
          -잠금해제 성공 시 PORTB의 LED 깜빡거림, UART 통신으로 " 잠금해제 성공"  메세지 출력
          -잠금해제 3번 실패시에 UART 통신으로 " 누군가가 잠금해제를 시도 중" 메세지 출력
          
          2. CDS(빛감지센서)을 이용해 주변 조도 감지
            - 조도에 따른 a/d 컨버터 값에 따른 PWM(ADC값에 따라 출력) 점등 (주변이 어두울 시에 PORTD가         
              점등된다)
              
          3. INT 4~7을 누를 때에 각각에 해당하는 숫자를 입력(INT4 : 1 , INT 5 : 2 , INT 6: 3 ,   
            INT 7 : 4)
            
         ![IMG_6431_2_MOV_AdobeExpress](https://user-images.githubusercontent.com/108858620/211215316-6b1bf64e-6701-4282-8a89-89c741794893.gif)
