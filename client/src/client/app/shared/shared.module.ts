import { NgModule, ModuleWithProviders } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { RouterModule } from '@angular/router';

import { NavbarComponent } from './navbar/index';
import { FooterComponent } from './footer/index';
import { WebSocketService } from './websocket/index';
import { SnifferService } from './sniffer/index';
import { PacketService } from './packet/index';
import { InterfaceService } from './interface/index';

@NgModule({
  imports: [CommonModule, RouterModule],
  declarations: [NavbarComponent, FooterComponent],
  exports: [
    NavbarComponent, FooterComponent, CommonModule, FormsModule, RouterModule
  ]
})
export class SharedModule {
  static forRoot(): ModuleWithProviders {
    return {
      ngModule: SharedModule,
      providers: [
        WebSocketService, SnifferService, PacketService, InterfaceService
      ]
    };
  }
}
