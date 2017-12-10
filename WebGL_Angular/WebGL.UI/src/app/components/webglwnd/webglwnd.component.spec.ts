import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { WebglwndComponent } from './webglwnd.component';

describe('WebglwndComponent', () => {
  let component: WebglwndComponent;
  let fixture: ComponentFixture<WebglwndComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ WebglwndComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(WebglwndComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
