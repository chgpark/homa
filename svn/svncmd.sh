#!bin/bash
SCFILE=/DATA/svn/repo/SOURCEPATH
USERNM=cpark
PASSWD=123456
SVNURL=svn://localhost

while getopts "ioelcus" opt; do
  case $opt in
    i)
      echo "Init mode was triggered." >&2
	  MODE=INIT
      ;;
	o)
	  echo "Checkout mode was triggered." >&2
	  MODE=CHKO
	  ;;
	e)
	  echo "EDIT mode was triggered." >&2
	  MODE=EDIT
	  ;;
	l)
	  echo "LOCK mode was triggered." >&2
	  MODE=LOCK
	  ;;
	c)
	  echo "COMMIT mode was triggered." >&2
	  MODE=CMMT
	  ;;
	u)
	  echo "UNLOCK mode was triggered." >&2
	  MODE=ULCK
	  ;;
	s)
	  echo "UPDATE TO SOURCE mode was triggered." >&2
	  MODE=UPSO
	  ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done
while [ -n "$MODE" ]; do
case $MODE in
	INIT)
		echo "Enter User ID"
		read -e USERNAME
		echo "Enter User Password"
		read -e USERPASSWORD
		sed '2s/.*/USERNM='"${USERNAME}"'/' svncmd.sh > tmp
		sed '3s/.*/PASSWD='"${USERPASSWORD}"'/' tmp > svncmd.sh
		rm -f tmp
		exit
		;;
	CHKO)
		echo "Enter directory name in the repository"
		read -e EXNM
		echo "Enter making path"
		read -e MKPATH
		if [ -n "$EXNM" ]; then
		if [ -n "$MKPATH" ]; then
		svn checkout $SVNURL/$EXNM $MKPATH --username $USERNM --password $PASSWD
		svn info $MKPATH
		svn log $MKPATH
		fi
		fi
		exit
		;;
	EDIT)
		echo "Enter working directory path"
		read -e WDPATH
		if [ -n "$WDPATH" ]; then
		svn info $WDPATH
		svn up $WDPATH
		MODE=LOCK
		else
		exit
		fi
		;;
	LOCK)
		echo "Enter locking target path"
		echo "Ex) KSE/PATH_TO_FILE"
		read -e LOCKNM
		if [ -n "$LOCKNM" ]; then
			if svn lock -m"$USERNM" $SVNURL/$LOCKNM --username $USERNM --password $PASSWD; then
			echo $LOCKNM >> LOCKED_FILELIST
			fi
		fi
		while [ -n "$LOCKNM" ]; do
			echo "Enter another path"
			read -e LOCKNM
			if [ -n "$LOCKNM" ]; then
				if svn lock -m"$USERNM" $SVNURL/$LOCKNM --username $USERNM --password $PASSWD; then
				echo $LOCKNM >> LOCKED_FILELIST
				fi
			fi
		done
		exit
		;;
	CMMT)
		echo "Enter working directory path"
		read -e WCPATH
		echo "Enter commit message"
		read -e CMMTMSG
		if [ -n "$WCPATH" ]; then
		svn commit -m "$CMMTMSG" $WCPATH --username $USERNM --password $PASSWD
		svn up $WCPATH
		svn info $WCPATH
		fi
		exit
		;;
	ULCK)
		echo "Enter locking target path"
		echo "Ex) KSE/PATH_TO_FILE"
		read -e ULCKNM
		if [ -n "$ULCKNM" ]; then
			if svn unlock $SVNURL/$ULCKNM --username $USERNM --password $PASSWD; then
			echo $ULCKNM >> UNLOCKED_FILELIST
			fi
		fi
		while [ -n "$ULCKNM" ]; do
			echo "Enter another path"
			read -e ULCKNM
			if [ -n "$ULCKNM" ]; then
				if svn unlock $SVNURL/$ULCKNM --username $USERNM --password $PASSWD; then
				echo $ULCKNM >> UNLOCKED_FILELIST
				fi
			fi
		done
		exit
		;;
	UPSO)
		echo "Enter REPOSITORY name"
		read -e REPONM
		if [ -n "$REPONM" ]; then
		SCPATH=$(cat $SCFILE|grep $REPONM|awk -F"=" '{print $2}')
		svn info $SCPATH
		echo "Are you sure to update this source?(y/n)"
		read -e ANSW
		if [ $ANSW == 'y' ]; then
		svn log -l 8 $SVNURL/$REPONM
		svn info $SVNURL/$REPONM
		echo "Enter revision number"
		read -e RVNB
		if [ -n "$RVNB" ]; then
		svn up $SCPATH -r $RVNB
		svn info $SCPATH
		fi
		fi
		fi
		exit
		;;
esac
done
