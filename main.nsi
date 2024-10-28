; NSIS betiği için tanımlamalar
Name "StudyTimer"
OutFile "StudyTimerInstaller.exe"
InstallDir "$PROGRAMFILES\StudyTimer"
Icon "studyt.ico"     ; Yükleyici simgesi

; Kullanıcı dizini seçimi için varsayılan dizin penceresi
Page directory
; Kurulum işlemi sayfası
Page instfiles

; Varsayılan dizini ayarla
Section "MainSection" 
  ; Dizini oluştur ve dosyaları kopyala
  SetOutPath "$INSTDIR"
  File "bin\StudyTimer_w64.exe"       ; Ana uygulama dosyası
  File "studyt.ico"                   ; İkon dosyası
  
  ; Music klasörünü oluştur
  CreateDirectory "$INSTDIR\sound"
  ; Çıktı yolunu music klasörüne değiştir
  SetOutPath "$INSTDIR\sound"      
  ; Müzik dosyasını music klasörüne kopyala
  File "sound\alarm1.wav"      


  ; Masaüstüne bir kısayol oluştur
  CreateShortcut "$DESKTOP\StudyTimer.lnk" "$INSTDIR\StudyTimer_w64.exe" "$INSTDIR\studyt.ico"

  ; Başlat menüsüne bir kısayol oluştur
  CreateDirectory "$SMPROGRAMS\StudyTimer"
  CreateShortcut "$SMPROGRAMS\StudyTimer\StudyTimer.lnk" "$INSTDIR\StudyTimer_w64.exe" "$INSTDIR\studyt.ico"

  ; Kaldırıcıyı oluştur
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

; Program kaldırıldığında yapılacaklar
Section "Uninstall"
  Delete "$INSTDIR\StudyTimer_w64.exe"
  Delete "$INSTDIR\studyt.ico"
  Delete "$INSTDIR\sound\alarm1.wav"  ; Müzik dosyasını music klasöründen kaldır
  Delete "$DESKTOP\StudyTimer.lnk"
  Delete "$SMPROGRAMS\StudyTimer\StudyTimer.lnk"
  RMDir "$SMPROGRAMS\StudyTimer"
  RMDir "$INSTDIR\sound"                  ; music klasörünü kaldır
  RMDir "$INSTDIR"
SectionEnd
