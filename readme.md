샘플 하나
시작점은 랜덤
루프
마우스 y값에 따라 샘플 몇 개 플레이하는지 결정 (1~100)
전체를 파일로 출력

liveOSC + oF app
에이블톤에서 녹음 걸어놓고 연주해부러
샘플 start, end 포인트 조절. (샘플 두 번 루프시킨 파일 만들고 그 중간 지점 전후로 고르면 편할 듯)
마우스에 따른 전체 레벨 조정


for i in *.mov; do ffmpeg -y -i "$i" -c:v libx264 -preset medium -b:v 2048k -pass 1 -c:a copy -f mp4 /dev/null && ffmpeg -i "$i" -c:v libx264 -preset medium -b:v 2048k -pass 2 -c:a copy "${i%.mov}.mp4"; done
