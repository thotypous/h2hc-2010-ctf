<?php

require "Exec.php";
require "Robot.php";

class SolveEight extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/eight/";
    const CAPTCHA_IMG = "https://192.168.1.3/eight/captcha/captcha.php";

    protected function captchaTreatment($contents) {
        $subject = trim($contents);

        if (!preg_match('/^[0-9]$/', $subject))
            return null;
        
        return $subject;
    }

}


$solveOne = new SolveEight("thebug", "thebug9988.-");
$points = 0;
while (true) {
    $points += $solveOne->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}
