#echo -en "\033[37;1;41m Readme \033[0m"

function comment {
  echo -ne "\033[32;2;40m"$1" \033[0m"
}
function comment_important {
  echo -ne "\033[32;1;40m"$1" \033[0m"
}

function error {
  echo -e "\033[37;1;41m  $1  \033[0m"
}

comment aaaaaaaa
comment_important aaaaaaaaa
error aaaaaaaaaaaaaa
