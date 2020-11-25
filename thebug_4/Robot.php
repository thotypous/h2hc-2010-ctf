<?php

abstract class Robot  {

    const CAPTCHA_URL = "https://192.168.1.3/number/";
    const CAPTCHA_IMG = "https://192.168.1.3/number/captcha.php";

    protected $user_agent = "Mozilla/1.22 (compatible; MSIE 2.1; Mac_PowerPC)";

    protected $username;
    protected $password;

    protected $cookie_file;
    protected $curl_resource;

    public function __construct($username, $password) {
        $this->username = $username;
        $this->password = $password;
        $this->initWebRequest();
    }

    /**
     * Envia dados para a web
     * @param string $url
     * @param array $formdata
     * @param int $expectedHttpCode
     * @param boolean $generateMeta
     * @return string
     */
    protected function postData($url, Array $formdata = array(), $expectedHttpCode = 200) {
        curl_setopt($this->curl_resource, CURLOPT_URL, $url);
        curl_setopt($this->curl_resource, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($this->curl_resource, CURLOPT_POST, !empty($formdata));
        curl_setopt($this->curl_resource, CURLOPT_POSTFIELDS, $formdata);

        $httpData = curl_exec($this->curl_resource);
        $errorCode = curl_getinfo($this->curl_resource, CURLINFO_HTTP_CODE);

        if ($expectedHttpCode !== null &&
                $errorCode != $expectedHttpCode)
            throw new Exception(sprintf("Código HTTP inesperado - %d", $errorCode));

        return $httpData;
    }


    protected function initWebRequest() {
        $this->cookie_file = tempnam(sys_get_temp_dir(), "CTF");
        $this->curl_resource = curl_init();
        curl_setopt($this->curl_resource, CURLOPT_USERAGENT, $this->user_agent);
        curl_setopt($this->curl_resource, CURLOPT_COOKIEFILE, "./cookie.txt");
        curl_setopt($this->curl_resource, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($this->curl_resource, CURLOPT_HEADER, 0);
        curl_setopt($this->curl_resource, CURLOPT_FOLLOWLOCATION, true);
    }

    protected function breakCaptcha() {
        $result = $this->captchaTreatment($this->postData(static::CAPTCHA_IMG));
        return $result;
    }

    protected function captchaTreatment(&$path) {
        return null;
    }

    public function play() {
        return $this->checkWin($this->getHTML(array(
            "captcha" => "13",
            "username" => $this->username,
            "passwd" => $this->password,
        )));
    }

    protected function checkWin($html) {
        return strstr($html, "<h3>BOT!</h3>") == false;
    }

    protected function getHTML(Array $formdata = array()) {
        return $this->postData(static::CAPTCHA_URL, $formdata);
    }

    /**
     * Finaliza chamada Web
     */
    protected function closeWebRequest() {
        curl_close($this->curl_resource);
        unlink($this->cookie_file);
    }

    public function __destruct() {
        $this->closeWebRequest();
    }


}
