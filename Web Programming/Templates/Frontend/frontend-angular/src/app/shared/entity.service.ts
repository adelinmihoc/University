import { Injectable } from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {map} from "rxjs/operators";
import {Observable} from "rxjs";
import {Entity} from "./entity.model";

@Injectable({
  providedIn: 'root'
})
export class EntityService {

  constructor(private httpClient: HttpClient) {
  }

  getAll(): Observable<Entity[]> {
    // const url = `http://localhost/Servers/php/getAll.php`;
    // const url = 'http://localhost:8080/api/getAll.jsp';
    const url = 'https://localhost:5001/api/getAll';
    const parents: Observable<Entity[]> = this.httpClient
      .get<Array<Entity>>(url);
    console.log(parents);
    return parents;
  }

  save(entity: Entity): Observable<Entity> {
    // const url = `http://localhost/Servers/php/add.php`;
    // const url = 'http://localhost:8080/api/add.jsp';
    const url = 'https://localhost:5001/api/add';
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Entity>("POST", url, {
      body: JSON.stringify(entity),
      responseType: 'json',
      headers: headers // asp good jsp bad
    });
  }

  delete(entity: Entity) {
    // const url = `http://localhost/Servers/php/delete.php`;
    // const url = 'http://localhost:8080/api/delete.jsp';
    const url = 'https://localhost:5001/api/delete';
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Entity>("POST", url, {
      body: JSON.stringify(entity),
      responseType: 'json',
      headers: headers // asp good jsp bad
    });
  }

  getOne(id: number): Observable<Entity> {
    // @ts-ignore
    return this.getAll()
      .pipe(
        map(entities => entities.find(entity => entity.id === id))
      );
  }

  update(entity: Entity) {
    // const url = `http://localhost/Servers/php/update.php`;
    // const url = 'http://localhost:8080/api/update.jsp';
    const url = 'https://localhost:5001/api/update';
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Entity>("POST", url, {
      body: JSON.stringify(entity),
      responseType: 'json',
      headers: headers // asp good jsp bad
    });
  }

  authenticate(entity: Entity): Observable<Entity> {
    // const url = `http://localhost/Servers/php/authentication.php`;
    // const url = 'http://localhost:8080/api/authentication.jsp';
    const url = 'https://localhost:5001/api/authenticate';
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Entity>("POST", url, {
      body: JSON.stringify(entity),
      responseType: 'json',
      headers: headers // asp good jsp bad
    });
  }

  register(entity: Entity): Observable<Entity> {
    // const url = `http://localhost/Servers/php/registration.php`;
    // const url = 'http://localhost:8080/api/registration.jsp';
    const url = 'https://localhost:5001/api/register';
    let headers = new HttpHeaders();
    headers = headers.append('content-type', 'application/json');
    return this.httpClient.request<Entity>("POST", url, {
      body: JSON.stringify(entity),
      responseType: 'json',
      headers: headers // asp good jsp bad
    });
  }
}
