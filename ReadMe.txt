**The resting position 
	= The lowest hyoid position
	= Start position of hyoid movement
	= The stable state
	≠ Burst start position

**Burst end frame
	= HMP_XY
		●	Hyoid bone이 xy축(대각)으로 최대 이동한 프레임

**11 Variables
	1)	Hyoid Movement Duration (HMD) 
		●	The resting position ~ Burst end position까지 소요된 시간

	2)	Hyoid Maximum Position (X) (HMP_X)
	3)	Hyoid Maximum Position (Y) (HMP_Y)
	4)	Hyoid Maximum Position (XY) (HMP_XY) ,  
		= Burst end position
		●	원점(C4) 기준 Burst end position의 좌표
		●	HMP_XY를 기준으로 HMP_X(HMP_XY의 x좌표)와 HMP_Y(HMP_XY의 y좌표) 결정
		●	HMP_XY와 별개로 다음 변수도 기록
			○	x축 최대 좌표
			○	y축 최대 좌표
	5)	Hyoid Maximum Displacement (Anterior) (HMD_A)
	6)	Hyoid Maximum Displacement (Superior) (HMD_S)
	7)	Hyoid Maximum Displacement (Hypotenuse) (HMD_H)
		●	The resting position으로부터 Burst end position까지의 변위

	8)	Hyoid Average Velocity (Anterior) (HAV_A) = HMD_A / HMD
	9)	Hyoid Average Velocity (Superior) (HAV_S) = HMD_S / HMD
	10)	Hyoid Average Velocity (Hypotenuse) (HAV_H)  = HMD_H / HMD
		●	Displacement의 기준과 HMD 기준을 통일 : The resting position ~ Burst end position

	11)	Hyoid Maximum Velocity  = Max(Velocity of each frame)
		●	각 프레임과 프레임 사이에서 hyoid bon의 가장 큰 속도
