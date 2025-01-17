#include <fstream>
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TStyle.h>

void DrawOverlappingHistograms() {
    // İstatistik kutusunu devre dışı bırak
    gStyle->SetOptStat(0);

    // Ortak binleme yapısı için histogram oluştur
    const int nBins = 100; // Ortak bin sayısı
    const double xMin = 0, xMax = 30; // 0-30 MeV enerji aralığı
    TH1F *hist1 = new TH1F("hist1", "44.txt", nBins, xMin, xMax);
    TH1F *hist2 = new TH1F("hist2", "13JAN_33_tab.lis", nBins, xMin, xMax);

    // 44.txt dosyasını oku ve histogramı doldur
    std::ifstream file1("44.txt");
    if (!file1.is_open()) {
        std::cerr << "44.txt dosyası açılamadı!" << std::endl;
        return;
    }

    std::string line;
    std::getline(file1, line); // Başlık satırını atla
    while (std::getline(file1, line)) {
        double center, content, error;
        std::stringstream ss(line);
        ss >> center >> content >> error;

        // Bin içeriklerini normalize et (1,000,000 ile böl)
        content /= 1e6;
        hist1->Fill(center, content); // Bin içeriklerini ekle
    }
    file1.close();

    // 13JAN_33_tab.lis dosyasını oku ve histogramı doldur
    std::ifstream file2("13JAN_33_tab.lis");
    if (!file2.is_open()) {
        std::cerr << "13JAN_33_tab.lis dosyası açılamadı!" << std::endl;
        return;
    }

    std::getline(file2, line); // Başlık satırlarını atla
    std::getline(file2, line);
    while (std::getline(file2, line)) {
        double energyLow, energyHigh, content, error;
        std::stringstream ss(line);
        ss >> energyLow >> energyHigh >> content >> error;

        // GeV'den MeV'e çevir
        energyLow *= 1000;
        energyHigh *= 1000;
        double binCenter = (energyLow + energyHigh) / 2.0;

        // Zaten normalize edilmiş içerikleri ekle
        if (energyHigh <= xMax) {
            hist2->Fill(binCenter, content);
        }
    }
    file2.close();

    // Çizim için kanvas oluştur
    TCanvas *c1 = new TCanvas("c1", "Histograms", 800, 600);
    c1->SetLogy(); // Y ekseni logaritmik

    // İlk histogramı çiz
    hist1->SetLineColor(kBlue);
    hist1->SetMarkerColor(kBlue);
    hist1->SetMarkerStyle(20);
    hist1->SetTitle("Overlay of 44.txt and 13JAN_33_tab.lis;Energy (MeV);Normalized Bin Content");
    hist1->Draw("HIST"); // Hata barları olmadan çiz

    // İkinci histogramı aynı kanvasa çiz
    hist2->SetLineColor(kRed);
    hist2->SetMarkerColor(kRed);
    hist2->SetMarkerStyle(21);
    hist2->Draw("HIST SAME"); // Hata barları olmadan çiz

    // Legend ekle ve yazı boyutunu büyüt
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(hist1, "44.txt (normalized)", "l");
    legend->AddEntry(hist2, "13JAN_33_tab.lis (already normalized)", "l");
    legend->SetTextSize(0.02); // Lejant yazı boyutunu ayarla
    legend->Draw();

    // Kanvası kaydet
    c1->SaveAs("overlay.png");
}
