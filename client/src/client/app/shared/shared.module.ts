import { NgModule, ModuleWithProviders } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { RouterModule } from '@angular/router';

import { NavbarComponent } from './navbar/index';
import { FooterComponent } from './footer/index';
import { WebSocketService } from './websocket/index';
import { SnifferClientService } from './sniffer-client/index';
import { SnifferConfigurationService } from './sniffer-configuration/index';

/**
 * Do not specify providers for modules that might be imported by a lazy loaded module.
 */

@NgModule({
  imports: [CommonModule, RouterModule],
  declarations: [NavbarComponent, FooterComponent],
  exports: [NavbarComponent, FooterComponent, CommonModule, FormsModule, RouterModule]
})
export class SharedModule {
  static forRoot(): ModuleWithProviders {
    return {
      ngModule: SharedModule,
      providers: [WebSocketService, SnifferClientService, SnifferConfigurationService]
    };
  }
}
