# Programlama 2 - Breakout (Tuğla Kırma) Oyunu

Bu proje, YZM104 - Programlama II dersi kapsamında C programlama dili ve SDL2 grafik kütüphanesi kullanılarak geliştirilmiş bir Breakout (Tuğla Kırma) oyunudur.

## Oyun Özellikleri
* **Klavye Kontrolü:** Raket (Paddle), klavyedeki Sol ve Sağ ok tuşları ile hareket ettirilir.
* **Can Sistemi:** Oyuncunun 3 canı vardır. Top ekranın altına düştüğünde 1 can azalır.
* **Gelişmiş Tuğlalar:** * Kırmızı Tuğlalar: 3 vuruşta kırılır.
  * Turuncu Tuğlalar: 2 vuruşta kırılır.
  * Yeşil Tuğlalar: 1 vuruşta kırılır.
  * Tuğlalar hasar aldıkça renk değiştirir.
* **Seviye Sistemi:** Ekrandaki tüm tuğlalar kırıldığında oyun yeni bir seviyeye geçer ve tuğlalar yeniden dizilir.

## Kurulum ve Derleme (Windows / MinGW)

Projeyi derlemek için sisteminizde `gcc` derleyicisi ve `SDL2` kütüphanesi kurulu olmalıdır. 

1. Repoyu bilgisayarınıza klonlayın.
2. Terminal üzerinden projenin bulunduğu dizine gidin.
3. Aşağıdaki komut ile projeyi derleyin:
   `mingw32-make`
   *(Not: Linux/macOS sistemlerde sadece `make` komutu yeterlidir.)*
4. Oyunu başlatmak için oluşan çalıştırılabilir dosyayı açın:
   `./breakout`

## Geliştirici
Bu proje özgün olarak geliştirilmiş ve tüm geliştirme aşamaları GitHub commit geçmişi ile kayıt altına alınmıştır.