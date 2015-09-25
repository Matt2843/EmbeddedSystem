;
; AutoHotkey Version: 1.x
; Language:       English
; Platform:       Win9x/NT
; Author:         A.N.Other <myemail@nowhere.com>
;
; Script Function:
;	Template script (you can customize this template by editing "ShellNew\Template.ahk" in your Windows folder)
;

#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.



	if(peak > THRESHOLD1){
		RR = eval_RR()
	
		if(RR_LOW<RR<RR_HIGH){
			normalRPeakFound()
			
		} else if(RR<RR_MISS){
			while(PEAKS[index-j] <= THRESHOLD2){
				j++
			}
			counter -= j
			
		}
		
		
	} else {
		notAnRPeak()
	}
	
	
	notAnRPeak(){
		NPKF = 0.125*peak+0.875*NPKF
		THRESHOLD1 = NPKF+0.25*(SPKF-NPKF)
		THRESHOLD2 = 0.5*THRESHOLD1
	}
	
	normalRPeakFound(){
		rPEAKS[index] = peak
		SPKF = 0.125*peak+0.875*SPKF
		RecentRR_OK[index] = RR
		RecentRR[index] = RR
		RR_Average2 = sum(RecentRR_OK)/8
		RR_Average1 = sum(RecentRR)/8
		RR_LOW = 0.92*RR_Average2
		RR_HIGH = 1.16*RR_Average2
		RR_MISS = 1.66*RR_Average2
		THRESHOLD1 = NPKF+0.25*(SPKF-NPKF)
		THRESHOLD2 = 0.5*THRESHOLD1
	}
	
	afterSearchBack(){
		rPEAKS[index] = PEAKS[index-j]
		SPKF = 0.25*rPEAKS[index]+0.75*SPKF
		RecentRR[index] = RR
		RR_Average1 = sum(RecentRR)/8
		RR_LOW = 0.92*RR_Average1
		RR_HIGH = 1.16*RR_Average1
		RR_MISS = 1.66*RR_Average1
		THRESHOLD1 = NPKF+0.25*(SPKF-NPKF)
		THRESHOLD2 = 0.5*THRESHOLD1
	}
	
	
	


