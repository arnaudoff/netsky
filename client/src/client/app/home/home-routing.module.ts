import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';

import { HomeComponent } from './home.component';

import { NewSessionComponent } from './new-session/new-session.component';
import { SessionSubscriptionComponent } from './session-subscription/session-subscription.component';

import { PasswordStepComponent } from './new-session/password-step/password-step.component';
import { InterfaceStepComponent } from './new-session/interface-step/interface-step.component';
import { FilterStepComponent } from './new-session/filter-step/filter-step.component';
import { StartStepComponent } from './new-session/start-step/start-step.component';

@NgModule({
  imports: [
    RouterModule.forChild([
      {
        path: 'home',
        component: HomeComponent,
        children: [
          {
            path: 'new',
            component: NewSessionComponent,
            children: [
              { path: '', redirectTo: 'password', pathMatch: 'full' },
              { path: 'password', component: PasswordStepComponent },
              { path: 'interface', component: InterfaceStepComponent },
              { path: 'filter', component: FilterStepComponent },
              { path: 'start', component: StartStepComponent }
            ]
          },
          { path: 'subscribe', component: SessionSubscriptionComponent }
        ]
      }
    ])
  ],
  exports: [RouterModule]
})
export class HomeRoutingModule { }
