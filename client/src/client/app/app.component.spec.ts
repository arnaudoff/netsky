import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { TestBed } from '@angular/core/testing';
import { APP_BASE_HREF } from '@angular/common';

import { async } from '@angular/core/testing';
import { Route } from '@angular/router';
import { RouterTestingModule } from '@angular/router/testing';

import { AppComponent } from './app.component';
import { NavbarComponent } from './shared/navbar/navbar.component';
import { FooterComponent } from './shared/footer/footer.component';

import { HomeComponent } from './home/home.component';
import { CaptureComponent } from './capture/capture.component';
import { PacketListComponent } from './packet-list/packet-list.component';

export function main() {

  describe('App component', () => {

    let config: Route[] = [
      { path: '', component: HomeComponent },
      { path: 'capture', component: CaptureComponent }
    ];

    beforeEach(() => {
      TestBed.configureTestingModule({
        imports: [FormsModule, RouterTestingModule.withRoutes(config)],
        declarations: [
          TestComponent, AppComponent, NavbarComponent, FooterComponent,
          HomeComponent, CaptureComponent, PacketListComponent
        ],
        providers: [
          { provide: APP_BASE_HREF, useValue: '/' }
        ]
      });
    });

    it('should build without a problem',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let compiled = fixture.nativeElement;

            expect(compiled).toBeTruthy();
          });
      }));
  });
}

@Component({
  selector: 'test-cmp',
  template: '<app></app>'
})

class TestComponent { }
