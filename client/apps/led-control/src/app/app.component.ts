import { Component, OnInit, ViewChild, ElementRef } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnInit {

    color: any;

    @ViewChild('colorInput')
    colorInput: ElementRef;


    constructor(private http: HttpClient) { }

    ngOnInit() { }

    setColor() {
        const el = this.colorInput.nativeElement as HTMLInputElement;
        this.http.post('http://localhost:3000/api/set-color', this.hexToRgbA(el.value)).subscribe(() => {});
    }

    private hexToRgbA(hex) {
        let c;
        if (/^#([A-Fa-f0-9]{3}){1,2}$/.test(hex)) {
            c = hex.substring(1).split('');
            if (c.length === 3) {
                c = [c[0], c[0], c[1], c[1], c[2], c[2]];
            }
            c = '0x' + c.join('');
            // tslint:disable-next-line:no-bitwise
            return {
                red: (c >> 16) & 255,
                green: (c >> 8) & 255,
                blue: c & 255
            };
        }
        throw new Error('Bad Hex');
    }

}
