import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from '../shared/shared.module';
import { HomeRoutingModule } from './home-routing.module';

import { NewSessionModule } from './new-session/new-session.module';
import { SessionSubscriptionModule }
from './session-subscription/session-subscription.module';

import { HomeComponent } from './home.component';

@NgModule({
  imports: [
    CommonModule, SharedModule, HomeRoutingModule, NewSessionModule,
    SessionSubscriptionModule],
  declarations: [HomeComponent],
  exports: [HomeComponent]
})
export class HomeModule {}
