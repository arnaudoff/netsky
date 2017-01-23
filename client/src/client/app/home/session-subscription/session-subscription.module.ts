import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../shared/shared.module';
import { SessionSubscriptionComponent } from './session-subscription.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [SessionSubscriptionComponent],
  exports: [SessionSubscriptionComponent]
})
export class SessionSubscriptionModule {}
