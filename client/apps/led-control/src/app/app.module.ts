import { NgModule } from '@angular/core';
import { AppComponent } from './app.component';
import { BrowserModule } from '@angular/platform-browser';
import { NxModule } from '@nrwl/nx';
import { RouterModule } from '@angular/router';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { HttpClientModule } from '@angular/common/http';

import { MatToolbarModule } from '@angular/material/toolbar';
import { FormsModule } from '@angular/forms';


@NgModule({
    imports: [
        BrowserModule,
        BrowserAnimationsModule,
        NxModule.forRoot(),
        RouterModule.forRoot([], { initialNavigation: 'enabled' }),
        MatToolbarModule,
        FormsModule,
        HttpClientModule
    ],
    declarations: [AppComponent],
    bootstrap: [AppComponent]
})
export class AppModule { }
