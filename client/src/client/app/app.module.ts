import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { APP_BASE_HREF } from '@angular/common';
import { RouterModule } from '@angular/router';
import { HttpModule } from '@angular/http';
import { AppComponent } from './app.component';
import { routes } from './app.routes';

import { SharedModule } from './shared/shared.module';
import { HomeModule } from './home/home.module';
import { CaptureModule } from './capture/capture.module';
import { PacketListModule } from './packet-list/packet-list.module';

@NgModule({
  imports: [
    BrowserModule, HttpModule, RouterModule.forRoot(routes),
    SharedModule.forRoot(), HomeModule, CaptureModule, PacketListModule],
  declarations: [AppComponent],
  providers: [{
    provide: APP_BASE_HREF,
    useValue: '<%= APP_BASE %>'
  }],
  bootstrap: [AppComponent]
})

export class AppModule { }
