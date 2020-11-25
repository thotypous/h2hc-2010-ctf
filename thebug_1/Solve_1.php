<?php

require "Exec.php";
require "Robot.php";

class SolveOne extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/one/";
    const CAPTCHA_IMG = "https://192.168.1.3/one/captcha.php";

    protected function captchaTreatment(&$image) {
        rename($image, ($image = "$image.jpg"));
        $subject = Exec::factory("./captcha01")
                ->setArgument($image)
                ->setStderr("/dev/null")
                ->call();

        return $subject;


    }

}


$solveOne = new SolveOne("thebug", "thebug9988.-");
$points = 0;
while (true) {
    $points += $solveOne->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}
