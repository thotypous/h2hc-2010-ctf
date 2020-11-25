<?php

require "Exec.php";
require "Robot.php";

class SolveFive extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/five/";

    public function play() {
        if (!preg_match("/([0-9]+)\s\+\s([0-9]+)/", $this->getHTML(), $match)) {
                throw new Exception("Regex!?");
        }

        return $this->checkWin($this->getHTML(array(
            "captcha" => (string)((int)$match[1] + (int)$match[2]),
            "username" => $this->username,
            "passwd" => $this->password,
        )));
    }

}


$solveTwo = new SolveFive("thebug", "thebug9988.-");
$points = 0;
while (true) {
    $points += $solveTwo->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}