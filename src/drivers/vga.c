#include <io.h>
#include <vga.h>

#define χρώμα 0x0F //white on black

θετικός μικρός *μνήμη_βίντεο = (θετικός μικρός *) 0xB8000;

θετικός ακαίρεος κερ_χ, κερ_ψ; //could use y but i dont wanna switch languages all the time

στατικός θετικός ακαίρεος πάρε_όφσετ() { //according to google translate, the greek translation of offset is offset
    επέστρεψε κερ_ψ * 80 + κερ_χ;
}

στατικός κενός μετακήνισε_κερ() {
    θετικός ακαίρεος οφ = πάρε_όφσετ();
    είσοδος(0x3D4, 14);
    είσοδος(0x3D5, οφ >> 8);
    είσοδος(0x3D4, 15);
    είσοδος(0x3D5, οφ);
}

κενός εκτύπωσε_χαρακτήρα(char χ) {
    θετικός μικρός *μ;

    αν (χ == '\n') {
        κερ_χ = 0;
        κερ_ψ++;
    } αλλιώς {
        μ = μνήμη_βίντεο + (πάρε_όφσετ());
        *μ = χ | (χρώμα << 8);
        κερ_χ++;
    }
    μετακήνισε_κερ();
}

κενός εκτύπωσε(char *χ) {
    γιά (ακαίρεος ι = 0; χ[ι] != '\0'; ι++) {
        εκτύπωσε_χαρακτήρα(χ[ι]);
    }
}

κενός καθάρισε_οθόνη() {
    γιά (ακαίρεος ι = 0; ι < 25 * 80; ι++) {
        μνήμη_βίντεο[ι] = 0x20 | (0x0F << 8);
    }
    κερ_χ = 0;
    κερ_ψ = 0;
    μετακήνισε_κερ();
}