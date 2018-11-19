# [...]

COLORFGBG='7;0'
EDITOR=vim
export COLORFGBG EDITOR
case "$TERM" in
    screen*) ;;
    *)
	case "$DISPLAY" in
	    localhost:1?.0) exec screen -x -p $(sed -e 's,localhost:1\(.\)\.0,\1,' <<< "$DISPLAY");;
	esac
	;;
esac
