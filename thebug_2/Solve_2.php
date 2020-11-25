<?php

require "Exec.php";
require "Robot.php";

class SolveTwo extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/two/";
    const CAPTCHA_IMG = "https://192.168.1.3/two/captcha.php";

    protected function captchaTreatment(&$image) {
        rename($image, ($image = "$image.jpg"));
        $subject = Exec::factory("/usr/bin/gocr")
                ->setArgument($image)
                ->setStderr("/dev/null")
                ->call();

        if (!preg_match("/([0-9]+)\s*([^\s]+)\s*([0-9]+)/", $subject, $match))
            return null;

        switch ($match[2]) {
            case "*":
                return (string)((int)$match[1] * (int)$match[3]);
                break;
            case "-":
                return (string)((int)$match[1] - (int)$match[3]);
                break;
            case "+":
                return (string)((int)$match[1] + (int)$match[3]);
                break;
            case "/":
                return (string)((int)$match[1] / (int)$match[3]);
                break;
        }

        return null;


    }

}


$solveTwo = new SolveTwo("thebug", "thebug9988.-");
$points = 0;
while (true) {
    $points += $solveTwo->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}